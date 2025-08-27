// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObserverComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/WorldInteractionMessage.h"
#include "Variant_MyActionGame/System/WorldInteractionSystem.h"


// Sets default values for this component's properties
UInteractableObserverComponent::UInteractableObserverComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractableObserverComponent::OnRegister()
{
	Super::OnRegister();

	UWorldInteractionSystem* WorldInteractionSystem = GetWorld()->GetSubsystem<UWorldInteractionSystem>();
	if (IsValid(WorldInteractionSystem))
	{
		WorldInteractionSystem->RegisterObserver(this);
	}
}

void UInteractableObserverComponent::OnUnregister()
{
	UWorldInteractionSystem* WorldInteractionSystem = GetWorld()->GetSubsystem<UWorldInteractionSystem>();
	if (IsValid(WorldInteractionSystem))
	{
		WorldInteractionSystem->UnregisterObserver(this);
	}
	
	Super::OnUnregister();
}

void UInteractableObserverComponent::OnEnterInteractable(class UInteractableObjectComponent* Interactable)
{
	BroadcastInteractionStatusChange(Interactable, EWorldInteractionStatus::Ready);
}

void UInteractableObserverComponent::OnLeaveInteractable(class UInteractableObjectComponent* Interactable)
{
	BroadcastInteractionStatusChange(Interactable, EWorldInteractionStatus::Invalid);
}

void UInteractableObserverComponent::BroadcastInteractionStatusChange(class UInteractableObjectComponent* Interactable, EWorldInteractionStatus NewStatus)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());

	FWorldInteractionMessage Msg;
	Msg.InteractionObserver = this;
	Msg.InteractionObject = Interactable;
	Msg.InteractionStatus = NewStatus;
	GameplayMessageSubsystem.BroadcastMessage(
			ActionGameGameplayTags::WorldInteraction_CanInteract,Msg);
}
