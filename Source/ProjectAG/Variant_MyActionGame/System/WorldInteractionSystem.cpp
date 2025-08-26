// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldInteractionSystem.h"

#include "Variant_MyActionGame/ActorComponent/InteractableObjectComponent.h"
#include "Variant_MyActionGame/ActorComponent/InteractableObserverComponent.h"


void UWorldInteractionSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UWorldInteractionSystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UWorldInteractionSystem::IsTickable() const
{
	return Observers.Num() > 0 && Interactables.Num() > 0;
}


void UWorldInteractionSystem::RegisterObserver(UInteractableObserverComponent* Observer)
{
	if (IsValid(Observer))
	{
		Observers.Add(Observer);
	}
}

void UWorldInteractionSystem::RegisterInteractable(UInteractableObjectComponent* Interactable)
{
	if (IsValid(Interactable))
	{
		Interactables.Add(Interactable);
	}
}

void UWorldInteractionSystem::UnregisterObserver(UInteractableObserverComponent* Observer)
{
	if (IsValid(Observer))
	{
		Observers.Remove(Observer);
	}
}

void UWorldInteractionSystem::UnregisterInteractable(UInteractableObjectComponent* Interactable)
{
	if (IsValid(Interactable))
	{
		Interactables.Remove(Interactable);
	}
}


void UWorldInteractionSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (UInteractableObserverComponent* Observer : Observers)
	{
		if (IsValid(Observer) == false) continue;

		const float RadiusSquared = Observer->GetObserveRadiusSquared();
		AActor* Owner = Observer->GetOwner();
		const FVector& OwnerLocation = Owner->GetActorLocation();
		
		for (UInteractableObjectComponent* Interactable : Interactables)
		{
			if (IsValid(Interactable) == false) continue;
			if (Interactable->CanInteract() == false) continue;
			
			AActor* InteractableOwner = Interactable->GetOwner();
			const FVector& InteractableLocation = InteractableOwner->GetActorLocation();

			const float DistSquared = (OwnerLocation - InteractableLocation).SquaredLength();
			if (DistSquared < RadiusSquared)
			{
				Observer->OnInteractableNearby(Interactable);
			}
		}
	}
}
