// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldInteractionSystem.generated.h"

/**
 * it collects interactable observers and interactables
 * notify observers if an interactable is found 
 */
UCLASS(MinimalAPI)
class UWorldInteractionSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	void RegisterObserver(class UInteractableObserverComponent* Observer);
	void RegisterInteractable(class UInteractableObjectComponent* Observer);
	void UnregisterObserver(class UInteractableObserverComponent* Observer);
	void UnregisterInteractable(class UInteractableObjectComponent* Observer);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;

private:
	UPROPERTY(Transient)
	TArray<class UInteractableObserverComponent*> Observers;

	UPROPERTY(Transient)
	TArray<class UInteractableObjectComponent*> Interactables;
	
};
