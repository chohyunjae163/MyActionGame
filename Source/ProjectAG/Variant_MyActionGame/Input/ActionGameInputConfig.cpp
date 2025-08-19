// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_MyActionGame/Input/ActionGameInputConfig.h"

#include "InputAction.h"

TObjectPtr<const UInputAction> UActionGameInputConfig::FindNativeInputAction(const FGameplayTag& GameplayTag) const
{
	for (const auto& [InputAction, InputTag] : NativeInputActions)
	{
		if (IsValid(InputAction) && InputTag == GameplayTag)
		{
			return InputAction;
		}
	}

	return nullptr;
}

TObjectPtr<const UInputAction> UActionGameInputConfig::FindAbilityInputAction(const FGameplayTag& GameplayTag) const
{
	for (const auto& [InputAction, InputTag] : AbilityInputActions)
	{
		if (IsValid(InputAction) && InputTag == GameplayTag)
		{
			return InputAction;
		}
	}

	return nullptr;		
}
