// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ActionGameInputConfig.generated.h"



class UInputAction;

USTRUCT()
struct FActionGameInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * 
 */
UCLASS(Const)
class PROJECTAG_API UActionGameInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	TObjectPtr<const UInputAction> FindNativeInputAction(const FGameplayTag& InputTag) const;
	TObjectPtr<const UInputAction> FindAbilityInputAction(const FGameplayTag& InputTag) const;
	
	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FActionGameInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FActionGameInputAction> AbilityInputActions;
};
