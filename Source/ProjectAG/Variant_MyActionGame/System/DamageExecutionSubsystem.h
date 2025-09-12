// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DamageExecutionSubsystem.generated.h"


/**
 * handles damage effect of the game world
 */
UCLASS(MinimalAPI)
class UDamageExecutionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:

	//receive hit data 
	static void RequestDamage(class UAbilitySystemComponent* AttackerASC, class UAbilitySystemComponent* TargetASC,const class UWeaponDefinition* AttackerWeapon);

private:
	static float GetCharacterStr(class UAbilitySystemComponent* AttackerASC);
	static void ApplyDamageGE(const class UAbilitySystemComponent* AttackerASC, float InRawDamage);
};
