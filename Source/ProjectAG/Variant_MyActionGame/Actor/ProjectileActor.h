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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void OnProjectileStopDelegate(const FHitResult& HitResult);
	
private:
	UPROPERTY()
	TObjectPtr<USceneComponent> DummyRoot;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;
	
};
