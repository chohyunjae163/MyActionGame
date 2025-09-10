// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DamageExecutionSubsystem.generated.h"


/**
 * handles damage effect of the game world
 */
UCLASS()
class PROJECTAG_API UDamageExecutionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:

	//receive hit data 
	void RequestDamage(class UAbilitySystemComponent* AttackerASC, class UAbilitySystemComponent* TargetASC);

private:
	float CalculateRawDamage(class UAbilitySystemComponent* AttackerASC);
	void ApplyDamageGE(const struct FGameplayEffectSpec& GameplayEffectSpec);
};
