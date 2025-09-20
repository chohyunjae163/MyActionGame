// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectileMovementComponent.h"

#include "FuncLib/ActionGameBPFuncLib.h"
#include "System/DamageExecutionSubsystem.h"


// Sets default values for this component's properties
UMyProjectileMovementComponent::UMyProjectileMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyProjectileMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	OnProjectileStop.AddDynamic(this,&ThisClass::OnHit);
	
}

void UMyProjectileMovementComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnProjectileStop.RemoveDynamic(this,&ThisClass::OnHit);
	
	Super::EndPlay(EndPlayReason);
}


void UMyProjectileMovementComponent::OnHit(const FHitResult& Hit)
{
	//if stopped, check what is happening
	//damage around the hit point
	AActor* HitActor = Hit.GetActor();
	UAbilitySystemComponent* Target = UActionGameBPFuncLib::GetAbilitySystemComponent(Cast<APawn>(HitActor));
	UWorld* World = GetWorld();
	UDamageExecutionSubsystem* DamageExecutionSubsystem = World->GetSubsystem<UDamageExecutionSubsystem>();
	DamageExecutionSubsystem->RequestDamageExecution(this,Target);
}

class UAbilitySystemComponent* UMyProjectileMovementComponent::GetMyAbilitySystemComponent() const
{
	//todo
	return nullptr;
}
