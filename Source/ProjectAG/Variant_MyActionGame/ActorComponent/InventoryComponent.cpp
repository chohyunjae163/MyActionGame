// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "ActionGameGameplayTags.h"
#include "Data/ItemDefinition.h"
#include "Engine/AssetManager.h"
#include "GameplayMessage/PlayerEventMessage.h"
#include "GameplayMessage/WorldInteractionMessage.h"
#include "SaveGame/MyLocalPlayerSaveGame.h"


DEFINE_LOG_CATEGORY(LogInventory)

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

	//load save data and fill inventory
	//after initialization of inventory component
	//tell viewmodel to update QuickSlot data
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
		PendingAssetsToAdd.Enqueue(Item.AssetId);
		const UItemDefinition* ItemDef = TryResolveDef(Item.AssetId);
		if (IsValid(ItemDef))
		{
			OnLoadAssetComplete();
		}
		else
		{
			TArray<FName> LoadBundles;
			UAssetManager::Get().LoadPrimaryAsset(Item.AssetId,LoadBundles,FStreamableDelegate::CreateUObject(this,&ThisClass::OnLoadAssetComplete));
		}

	}

}

void UInventoryComponent::AddItem(const FPrimaryAssetId& Id, const UItemDefinition* ItemDef,int32 NewQuantity)
{
	if (IsValid(ItemDef))
	{
		FInventoryItemHandle Handle = FInventoryItemHandle::NewHandle(ItemDef->GetPathName());
		if (FItemInstance* ItemInstance = FindItem(Handle))
		{
			ItemInstance->Quantity += NewQuantity;
		}
		else
		{
			FItemInstance NewItemInstance
			{
				.Handle = Handle,
				.ItemAssetId = Id,
				.Quantity = NewQuantity,  // quantity temporary
				.QuickSlotIndex = 0, // Quick Slot Test  
			};
			
			ItemList.Emplace(NewItemInstance);
		}
	}
}

FItemInstance* UInventoryComponent::FindItem(const FInventoryItemHandle& ItemHandle)
{
	return  ItemList.FindByPredicate([ItemHandle](FItemInstance& Item)
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

		if (ItemInstance->Quantity <= 0)
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
		ItemList.Remove(*ItemInstance);
	}
}

const UItemDefinition* UInventoryComponent::TryResolveDef(const FPrimaryAssetId& Id)
{
	UItemDefinition* ItemDef = Cast<UItemDefinition>(UAssetManager::Get().GetPrimaryAssetObject(Id));
	if (IsValid(ItemDef))
	{
		return ItemDef;
	}
	
	return nullptr;

}

void UInventoryComponent::OnLoadAssetComplete()
{
	FPrimaryAssetId Id;
	if (PendingAssetsToAdd.Dequeue(Id))
	{
		const UItemDefinition* ItemDefinition = TryResolveDef(Id);
		if (ensure(IsValid(ItemDefinition)))
		{
			AddItem(Id,ItemDefinition,1);
		}
	}

	if (PendingAssetsToAdd.IsEmpty())
	{
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		GameplayMessageSubsystem.BroadcastMessage(
			ActionGameGameplayTags::PlayerEvent_InventoryUpdated,
			FPlayerInventoryUpdated { ItemList });
	}
}

void UInventoryComponent::WriteToSave(class USaveGame* SaveGameObject)
{
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	if (IsValid(LocalPlayerSaveGame))
	{
		LocalPlayerSaveGame->ItemRecords.Empty();
		for (const FItemInstance& ItemInstance : ItemList)
		{
			LocalPlayerSaveGame->ItemRecords.Add(
				FItemRecord(
					ItemInstance.ItemAssetId,
					ItemInstance.Quantity)
					);
		}
	}
}

void UInventoryComponent::ReadFromSave(class USaveGame* SaveGameObject)
{
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	if (IsValid(LocalPlayerSaveGame))
	{
		for (const FItemRecord Record : LocalPlayerSaveGame->ItemRecords)
		{
			const UItemDefinition* ItemDef = TryResolveDef(Record.Id);
			AddItem(Record.Id,ItemDef,Record.Quantity);
		}
	}
}
