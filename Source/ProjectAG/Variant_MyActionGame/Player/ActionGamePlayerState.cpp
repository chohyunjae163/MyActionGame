// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerState.h"
#include "AbilitySystemComponent.h"
#include "ActionGameGameplayTags.h"
#include "ActorComponent/EquipmentComponent.h"
#include "ActorComponent/InventoryComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameplayMessage/UIViewMessage.h"
#include "Variant_MyActionGame/ActorComponent/MyAbilitySystemComponent.h"
#include "Variant_MyActionGame/GameplayAttribute/ActionGameCharacterAttributeSet.h"



class UMVVMGameSubsystem;

AActionGamePlayerState::AActionGamePlayerState(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("MyInventory"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("MyEquipment"));
	
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("MyAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//...

	PlayerAttributeSet = CreateDefaultSubobject<UActionGameCharacterAttributeSet>(TEXT("MyPlayerAttributeSet"));

	
}

UAbilitySystemComponent* AActionGamePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<FQuickSlotData> AActionGamePlayerState::ViewQuickSlot() const
{
	TArray<FQuickSlotData> Ret;
	Ret.Reserve(NUM_QUICK_SLOT);
	for (int i  = 0; i < NUM_QUICK_SLOT; ++i)
	{
		Ret.Add(QuickSlotItems[i]);
	}
	return Ret;
}

void AActionGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	QuickSlotChangeListenerHandle = GameplayMessageSubsystem.RegisterListener(
	ActionGameGameplayTags::UIEvent_QuickSlotChanged,
	this,
	&ThisClass::OnQuickSlotItemChanged);
	
}

void AActionGamePlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(QuickSlotChangeListenerHandle);
	Super::EndPlay(EndPlayReason);
}

void AActionGamePlayerState::OnQuickSlotItemChanged(struct FGameplayTag Channel,
                                                    const struct FUI_QuickSlotChangedMessage& Message)
{
	if (Message.ItemAssetId.IsValid() == false)
	{
		return;
	}
	if (INDEX_NONE < Message.Index && Message.Index < NUM_QUICK_SLOT)
	{
		return;
	}

	QuickSlotItems[Message.Index].ItemAssetId = Message.ItemAssetId;
	QuickSlotItems[Message.Index].Quantity = Message.Quantity;	
}
