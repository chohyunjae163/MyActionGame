// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectComponent.h"

#include "Variant_MyActionGame/System/WorldInteractionSystem.h"


// Sets default values for this component's properties
UInteractableObjectComponent::UInteractableObjectComponent():bInteractable(true)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UInteractableObjectComponent::CanInteract() const
{
	return bInteractable;
}

void UInteractableObjectComponent::OnRegister()
{
	Super::OnRegister();
	
	UWorldInteractionSystem* WorldInteractionSystem = GetWorld()->GetSubsystem<UWorldInteractionSystem>();
	if (IsValid(WorldInteractionSystem))
	{
		WorldInteractionSystem->RegisterInteractable(this);
	}
}

void UInteractableObjectComponent::OnUnregister()
{
	UWorldInteractionSystem* WorldInteractionSystem = GetWorld()->GetSubsystem<UWorldInteractionSystem>();
	if (IsValid(WorldInteractionSystem))
	{
		WorldInteractionSystem->UnregisterInteractable(this);
	}
	
	Super::OnUnregister();

	
}
