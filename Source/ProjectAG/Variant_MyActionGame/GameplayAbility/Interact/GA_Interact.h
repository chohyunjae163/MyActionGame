// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Interact.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UGA_Interact : public UGameplayAbility
{
	GENERATED_BODY()

	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	virtual void OnMontageFinished();
	UFUNCTION()
	virtual void OnMontageInterrupted();
	UFUNCTION()
	virtual void OnMontageCancelled();

protected:
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	TObjectPtr<UAnimMontage> 	MontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	float PlayRate = 1.0f;
};
