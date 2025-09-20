// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameActor.h"
#include "ProjectileActor.generated.h"

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

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DummyRoot;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
