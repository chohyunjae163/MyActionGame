// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"


/**
 * Collect InputTags
 * Process Them
 * Make sure to clear them after the process on the same frame
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTAG_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyAbilitySystemComponent();
	
	void AbilityInputTagPressed(const struct FGameplayTag& InputTag);
	void AbilityInputTagReleased(const struct FGameplayTag& InputTag);
	
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

private:
	TArray<FGameplayTag> InputPressedTags;
	TArray<FGameplayTag> InputReleasedTags;
};
