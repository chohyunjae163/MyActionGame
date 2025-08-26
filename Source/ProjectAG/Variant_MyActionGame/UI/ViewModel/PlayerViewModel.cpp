// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewModel.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/GameplayMessage/WorldInteractionMessage.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"

void UPlayerViewModel::Initialize(UAbilitySystemComponent* ASC)
{
	Super::Initialize(ASC);
	UGameplayMessageSubsystem& GameplayMessageSubsystem =UGameplayMessageSubsystem::Get(GetWorld());

	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::WorldInteraction_CanInteract,
		this,
		&ThisClass::OnInteractableFound);	
}

void UPlayerViewModel::Deinitialize(UAbilitySystemComponent* ASC) const
{
	if (ListenerHandle.IsValid())
	{
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		GameplayMessageSubsystem.UnregisterListener(ListenerHandle);
	}

	Super::Deinitialize(ASC);
}

void UPlayerViewModel::OnInteractableFound(struct FGameplayTag Channel, const struct FWorldInteractionMessage& Msg)
{
	const bool CanInteract = Msg.InteractionStatus == EWorldInteractionStatus::Available;
	UE_MVVM_SET_PROPERTY_VALUE(bInteractable,CanInteract);
}
