// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionSubsystem.h"

#include "AbilitySystemComponent.h"
#include "GameplayAttribute/ActionGameCharacterAttributeSet.h"
#include "GameplayEffect/GameplayEffect_Damage.h"

void UDamageExecutionSubsystem::RequestDamage(class UAbilitySystemComponent* AttackerASC,
                                              class UAbilitySystemComponent* TargetASC)
{
	FGameplayEffectSpecHandle SpecHandle = AttackerASC->MakeOutgoingSpec(UGameplayEffect_Damage::StaticClass(),1,AttackerASC->MakeEffectContext());

	FGameplayTag GameplayTag;


	
	float RawDamage = CalculateRawDamage(AttackerASC);
	SpecHandle.Data->SetSetByCallerMagnitude(GameplayTag,RawDamage);
	
	ApplyDamageGE(*SpecHandle.Data.Get());

	
}

float UDamageExecutionSubsystem::CalculateRawDamage(class UAbilitySystemComponent* AttackerASC)
{
	if (IsValid(AttackerASC) == false)
	{
		return 0.0f;
	}
	const UActionGameCharacterAttributeSet* AttributeSet = Cast<UActionGameCharacterAttributeSet>(AttackerASC->GetAttributeSet(UActionGameCharacterAttributeSet::StaticClass()));
	if (IsValid(AttributeSet) == false)
	{
		return 0.0f;
	}
	float RawDamage  = 0.0f;
	
	return RawDamage;
}

void UDamageExecutionSubsystem::ApplyDamageGE(const struct FGameplayEffectSpec& GameplayEffectSpec)
{
}
