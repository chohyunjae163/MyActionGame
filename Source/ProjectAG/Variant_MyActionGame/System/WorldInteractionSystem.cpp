// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldInteractionSystem.h"

#include "Variant_MyActionGame/ActorComponent/InteractableObjectComponent.h"
#include "Variant_MyActionGame/ActorComponent/InteractableObserverComponent.h"
#include "Variant_MyActionGame/GameplayMessage/WorldInteractionMessage.h"


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
		ObserverInteractionStatus.Add(EWorldInteractionStatus::Invalid);
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

	//check observer enter/leave interactables
	for (int32 i = 0; i < Observers.Num(); i++)
	{
		if (IsValid(Observers[i]) == false) continue;
		if (ObserverInteractionStatus[i] == EWorldInteractionStatus::Interacting) continue;

		const float RadiusSquared = Observers[i]->GetObserveRadiusSquared();
		AActor* Owner = Observers[i]->GetOwner();
		const FVector& OwnerLocation = Owner->GetActorLocation();

		for (int32 j = 0; j < Interactables.Num(); j++)
		{
			if (IsValid(Interactables[j]) == false) continue;
			if (Interactables[j]->CanInteract() == false) continue;
			
			AActor* InteractableOwner = Interactables[j]->GetOwner();
			const FVector& InteractableLocation = InteractableOwner->GetActorLocation();
			const float DistSquared = (OwnerLocation - InteractableLocation).SquaredLength();
			if (ObserverInteractionStatus[i] == EWorldInteractionStatus::Invalid)
			{
				if (DistSquared < RadiusSquared)
				{
					Observers[i]->OnEnterInteractable(Interactables[i]);
					ObserverInteractionStatus[i] = EWorldInteractionStatus::Ready;
				}				
			}
			else if (ObserverInteractionStatus[i] == EWorldInteractionStatus::Ready)
			{
				if (DistSquared > RadiusSquared)
				{
					Observers[i]->OnLeaveInteractable(Interactables[i]);
					ObserverInteractionStatus[i] = EWorldInteractionStatus::Invalid;
				}
			}
		}
	}
	
}
