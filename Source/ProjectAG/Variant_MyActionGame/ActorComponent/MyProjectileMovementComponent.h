// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/DamageCauserInterface.h"
#include "MyProjectileMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTAG_API UMyProjectileMovementComponent : public UProjectileMovementComponent,public IDamageCauserInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyProjectileMovementComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void OnHit(const FHitResult& Hit);

		
	// begin IDamageCauserInterface
	virtual class UAbilitySystemComponent* GetMyAbilitySystemComponent() const override;
	virtual TObjectPtr<APawn> GetDamageCauserPawn() const override;
	// end IDamageCauserInterface
};
