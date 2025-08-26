// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnComponent.h"
#include "InteractableObserverComponent.generated.h"


/**
 * this component is added to a pawn.
 * this component should deal with interactables nearby.
 */
UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInteractableObserverComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableObserverComponent(const FObjectInitializer& ObjectInitializer);

	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	FORCEINLINE float GetObserveRadius() const { return ObserveRadius; };
	FORCEINLINE float GetObserveRadiusSquared() const { return ObserveRadius*ObserveRadius; };

	void OnInteractableNearby(class UInteractableObjectComponent* Interactable);
protected:
	UPROPERTY(EditAnywhere, Category="World Interaction",meta=(UIMin=50,UIMax=500,ClampMin=50,ClampMax=500))
	float ObserveRadius = 100.f;
};
