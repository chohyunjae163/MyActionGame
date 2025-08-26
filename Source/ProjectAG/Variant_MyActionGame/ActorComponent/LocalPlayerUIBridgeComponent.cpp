// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalPlayerUIBridgeComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/WorldInteractionMessage.h"

// Sets default values for this component's properties
ULocalPlayerUIBridgeComponent::ULocalPlayerUIBridgeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULocalPlayerUIBridgeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UGameplayMessageSubsystem& GameplayMessageSubsystem =UGameplayMessageSubsystem::Get(GetWorld());

	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::WorldInteraction_CanInteract,
		this,
		&ThisClass::OnInteractableFound);	
	
}

void ULocalPlayerUIBridgeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ListenerHandle.IsValid())
	{
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		GameplayMessageSubsystem.UnregisterListener(ListenerHandle);
	}

	Super::EndPlay(EndPlayReason);
}

void ULocalPlayerUIBridgeComponent::OnInteractableFound(FGameplayTag Channel,
                                                        const FWorldInteractionMessage& Msg)
{
	
}



