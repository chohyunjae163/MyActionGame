// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_MyActionGame/Input/ActionGameInputConfig.h"

#include "InputAction.h"

TObjectPtr<const UInputAction> UActionGameInputConfig::FindNativeInputAction(const FGameplayTag& InputTag) const
{
	for (const FActionGameInputAction& Action : NativeInputActions)
	{
		if (IsValid(Action.InputAction) && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}
