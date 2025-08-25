// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ActionGameInteractableObjectComponent.generated.h"


/**
 * attach this component to any actor that wants to interact with pawns. (e.g. a chest box, a simple pickup)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,DisplayName=InteractableObject))
class PROJECTAG_API UActionGameInteractableObjectComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActionGameInteractableObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
