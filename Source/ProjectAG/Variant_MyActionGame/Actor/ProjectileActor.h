// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameActor.h"
#include "ProjectileActor.generated.h"


/*
 * a base class for projectiles blueprint
 */
UCLASS(MinimalAPI)
class AProjectileActor : public AActionGameActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileActor();

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> DummyRoot;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;
	
};
