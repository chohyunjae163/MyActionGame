// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameInputConfig.h"
#include "EnhancedInputComponent.h"
#include "ActionGameInputComponent.generated.h"

/**
 * Component used to manage input mappings and bindings using an input config data asset.
 */
UCLASS()
class PROJECTAG_API UActionGameInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType>
	void BindNativeAction(
		const UActionGameInputConfig* InputConfig,
		const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent,
		UserClass* Object,
		FuncType Func);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(
		const UActionGameInputConfig* InputConfig,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename FuncType>
void UActionGameInputComponent::BindNativeAction(const UActionGameInputConfig* InputConfig,
	const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	//
	if (const UInputAction* InputAction = InputConfig->FindNativeInputAction(InputTag))
	{
		BindAction(InputAction, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UActionGameInputComponent::BindAbilityActions(const UActionGameInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	for (const FActionGameInputAction& Action  : InputConfig->AbilityInputActions)
	{
		if (PressedFunc)
		{
			BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,PressedFunc,Action.InputTag);
		}
		if (ReleasedFunc)
		{
			BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,ReleasedFunc,Action.InputTag);
		}
		
	}
}
