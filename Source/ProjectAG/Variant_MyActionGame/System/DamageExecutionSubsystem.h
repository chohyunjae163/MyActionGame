// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DamageExecutionSubsystem.generated.h"


/**
 * handles damage effect of the game world
 */
UCLASS(Abstract,MinimalAPI,Blueprintable)
class UDamageExecutionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	//receive hit data 
	void RequestDamageExecution(class UAbilitySystemComponent* AttackerASC, class UAbilitySystemComponent* TargetASC);

protected:
	//do damage calculation on the blueprint
	UFUNCTION(BlueprintImplementableEvent)
	float CalculateDamage(float WeaponDamage,float CharacterStr);
private:
	static float GetCharacterStr(class UAbilitySystemComponent* AttackerASC);
};
