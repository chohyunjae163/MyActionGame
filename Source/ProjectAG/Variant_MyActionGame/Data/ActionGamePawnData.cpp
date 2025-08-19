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

