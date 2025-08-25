// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePawnData.h"

#include "AbilitySystemComponent.h"

UActionGameAbilitySet::UActionGameAbilitySet(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UActionGameAbilitySet::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent)
{
	for (auto AbilityClass : GrantedGameplayAbilities)
	{
		if (IsValid(AbilitySystemComponent))
		{
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void UActionGameAbilitySet::ApplyEffects(UAbilitySystemComponent* AbilitySystemComponent)
{
	for (TSubclassOf<UGameplayEffect> EffectClass : GrantedGameplayEffects)
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass,1,ContextHandle);
		if(ensure(EffectSpecHandle.Data.IsValid()))
		{
			TSharedRef<FGameplayEffectSpec> Spec = EffectSpecHandle.Data.ToSharedRef();
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(Spec.Get());		
		}
	}
}

