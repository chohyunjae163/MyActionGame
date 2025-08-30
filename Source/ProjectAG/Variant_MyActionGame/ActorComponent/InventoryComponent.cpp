// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "ActionGameGameplayTags.h"
#include "Data/ItemDefinition.h"
#include "Engine/AssetManager.h"
#include "GameplayMessage/WorldInteractionMessage.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::WorldInteraction_PickupItem,
		this,
		&ThisClass::OnWorldInteractItem);
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(ListenerHandle);
	
	Super::EndPlay(EndPlayReason);
}

void UInventoryComponent::OnWorldInteractItem(struct FGameplayTag Channel,
	const FInstancedStruct& Message)
{
	FWorldItemInteractionPayload Payload = Message.Get<FWorldItemInteractionPayload>();
	for (const FWorldInteractionItemUnit& Item : Payload.Items)
	{
		TryAddItem(Item.AssetId);
	}

}

void UInventoryComponent::TryAddItem(const FPrimaryAssetId& ItemAssetId)
{
	const UItemDefinition* ItemDef = ResolveDef(ItemAssetId);

	if (IsValid(ItemDef))
	{
		FInventoryItemHandle Handle = FInventoryItemHandle::NewHandle(ItemDef->GetPathName());
		if (FItemInstance* ItemInstance = FindItem(Handle))
		{
			ItemInstance->Quantity++;
		}
		else
		{
			Items.Emplace( FItemInstance
			{
				.Handle = Handle,
				.ItemAssetId = ItemAssetId,
				.Quantity = 1
			});		
		}
	}
}

FItemInstance* UInventoryComponent::FindItem(const FInventoryItemHandle& ItemHandle)
{
	return  Items.FindByPredicate([ItemHandle](FItemInstance& Item)
	{
		return Item.Handle == ItemHandle;
	});
}

void UInventoryComponent::UseItem(const FInventoryItemHandle& ItemHandle)
{
	if (FItemInstance* ItemInstance = FindItem(ItemHandle))
	{
		if (ItemInstance->Quantity > 0)
		{
			ItemInstance->Quantity--;
		}

		if (ItemInstance->Quantity == 0)
		{
			//remove
			RemoveItem(ItemHandle);
		}
	}
}


void UInventoryComponent::RemoveItem(FInventoryItemHandle Handle)
{
	if (FItemInstance* ItemInstance = FindItem(Handle))
	{
		Items.Remove(*ItemInstance);
	}
}


const UItemDefinition* UInventoryComponent::ResolveDef(const FPrimaryAssetId& Id)
{
	UItemDefinition* ItemDef = Cast<UItemDefinition>(UAssetManager::Get().GetPrimaryAssetObject(Id));
	if (IsValid(ItemDef))
	{
		return ItemDef;
	}

	TArray<FName> LoadBundles;
	UAssetManager::Get().LoadPrimaryAsset(Id,LoadBundles,FStreamableDelegate::CreateUObject(this,&ThisClass::OnLoadAssetComplete));
	PendingAssetsToAdd.Enqueue(Id);
	return nullptr;

}

void UInventoryComponent::OnLoadAssetComplete()
{
	FPrimaryAssetId Id;
	if (PendingAssetsToAdd.Dequeue(Id))
	{
		TryAddItem(Id);
	}
}
