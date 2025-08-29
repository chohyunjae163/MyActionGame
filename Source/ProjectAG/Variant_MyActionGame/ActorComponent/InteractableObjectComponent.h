// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SphereComponent.h"
#include "StructUtils/InstancedStruct.h"
#include "InteractableObjectComponent.generated.h"



// interactable objects must have a spec ( maybe more than one..?)
USTRUCT()
struct FInteractionSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="World Interaction")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere,Category="World Interaction")
	FInstancedStruct Payload;

	UPROPERTY(EditAnywhere,Category="World Interaction")
	TObjectPtr<UAnimMontage> InstigatorMontage;

	UPROPERTY(EditAnywhere,Category="World Interaction",meta=(MakeEditWidget))
	FTransform InstigatorTransform;
	
};

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
	FORCEINLINE const FInteractionSpec& GetInteractionSpec() const { return InteractionSpec; }

	// handle vfx/sfx
	UFUNCTION(BlueprintImplementableEvent, Category="World Interaction")
	void OnInteract();
protected:
	//~ Begin ActorComponent Interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	//~ End ActorComponent Interface
	
protected:
	UPROPERTY(EditInstanceOnly,Category="World Interaction")
	bool bInteractable;

	UPROPERTY(EditInstanceOnly,Category="World Interaction")
	FInteractionSpec InteractionSpec;

};
