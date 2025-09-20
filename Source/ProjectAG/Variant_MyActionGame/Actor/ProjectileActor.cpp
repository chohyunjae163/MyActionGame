// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

#include "GameFramework/ProjectileMovementComponent.h"


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

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->OnProjectileStop.AddDynamic(this,&ThisClass::OnProjectileStopDelegate);
	
}

void AProjectileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MovementComponent->OnProjectileStop.RemoveDynamic(this,&ThisClass::OnProjectileStopDelegate);
	Super::EndPlay(EndPlayReason);
}

void AProjectileActor::OnProjectileStopDelegate(const FHitResult& HitResult)
{
	//if stopped, check what is happening
	//damage around the hit point
}

