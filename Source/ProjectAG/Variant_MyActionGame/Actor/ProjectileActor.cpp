// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

#include "AbilitySystemComponent.h"
#include "FuncLib/ActionGameBPFuncLib.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "System/DamageExecutionSubsystem.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DummyRoot;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);
}
