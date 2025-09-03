// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewModel.h"

#include "Data/ItemDefinition.h"
#include "Engine/AssetManager.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameplayMessage/CharacterEventMessage.h"
#include "GameplayMessage/UIViewMessage.h"
#include "Player/ActionGamePlayerState.h"
#include "Variant_MyActionGame/GameplayMessage/WorldInteractionMessage.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"


void UPlayerViewModel::Initialize(class AActionGamePlayerState* PlayerState)
{
	UAbilitySystemComponent* ASC = PlayerState->GetAbilitySystemComponent();
	Super::Initialize(ASC);
	
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());

	ListenerHandles.Add(GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::WorldInteraction_CanInteract,
		this,
		&ThisClass::OnInteractableFound));

	ListenerHandles.Add(GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::CharacterEvent,
		this,
		&ThisClass::OnUseConsumable
		));

	QuickSlotItemData.Empty();
	TArray<FQuickSlotData> PlayerQuickSlot = PlayerState->ViewQuickSlot();
	
	for (const FQuickSlotData Data : PlayerQuickSlot)
	{
		if (Data.ItemAssetId.IsValid())
		{
			FItemViewData ItemViewData;
			ItemViewData.Quantity = Data.Quantity;
			ItemViewData.AssetId = Data.ItemAssetId;
			QuickSlotItemData.Add(ItemViewData);		
		}
	}

	for (FItemViewData& ItemViewData : QuickSlotItemData)
	{
		TArray<FName> LoadBundles;
		UAssetManager::Get().LoadPrimaryAsset(ItemViewData.AssetId,LoadBundles,FStreamableDelegate::CreateLambda([&ItemViewData]()
		{
			UItemDefinition* ItemDef = Cast<UItemDefinition>(UAssetManager::Get().GetPrimaryAssetObject(ItemViewData.AssetId));
			ItemViewData.Icon = ItemDef->Icon;
		}));
	}
}

void UPlayerViewModel::Deinitialize() const
{
	for (const FGameplayMessageListenerHandle& ListenerHandle : ListenerHandles)
	{
		if (ListenerHandle.IsValid())
		{
			UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
			GameplayMessageSubsystem.UnregisterListener(ListenerHandle);
		}	
	}
	
	Super::Deinitialize();
}


void UPlayerViewModel::OnQuickSlotItemChanged(int32 Index)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	FUI_QuickSlotChangedMessage Msg;
	//Msg.ItemAssetId = 0;
	//Msg.Index = Index;
	//Msg.Quantity = 0;
	GameplayMessageSubsystem.BroadcastMessage(ActionGameGameplayTags::UIEvent_QuickSlotChanged,Msg);
}

void UPlayerViewModel::OnInteractableFound(struct FGameplayTag Channel, const struct FWorldInteractionMessage& Msg)
{
	const bool CanInteract = Msg.InteractionStatus == EWorldInteractionStatus::Ready;
	UE_MVVM_SET_PROPERTY_VALUE(bInteractable,CanInteract);
}

void UPlayerViewModel::OnUseConsumable(struct FGameplayTag Channel, const struct FCharacterConsumableMessage& Msg)
{
	const int32 SlotIndex = Msg.SlotIndex;

	QuickSlotItemData[SlotIndex].Quantity -= 1;

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetQuickSlotItems);
}

TArray<FItemViewData> UPlayerViewModel::GetQuickSlotItems() const
{
	return QuickSlotItemData;
}

