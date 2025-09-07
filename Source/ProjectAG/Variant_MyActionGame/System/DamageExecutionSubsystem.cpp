// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionSubsystem.h"

#include "AbilitySystemComponent.h"

void UDamageExecutionSubsystem::RequestDamage(class UAbilitySystemComponent* CauserASC,
                                              class UAbilitySystemComponent* TargetASC)
{
	FGameplayEffectSpec GameplayEffectSpec;
	//GameplayEffectSpec.Def;
	TargetASC->ApplyGameplayEffectSpecToSelf(GameplayEffectSpec);
}
