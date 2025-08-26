// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableObjectComponent.generated.h"


/**
 * attach this component to any actor that wants to interact with pawns. (e.g. a chest box, a simple pickup)
 * this component is used as a tag  when a character tries to find interactables around it.
 */
UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,DisplayName=InteractableObject))
class UInteractableObjectComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableObjectComponent();

	bool CanInteract() const;
protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;


	
protected:
	UPROPERTY(EditInstanceOnly,Category="World Interaction")
	bool bInteractable;
};
