// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"


// Sets default values for this component's properties
UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMyAbilitySystemComponent::AbilityInputTagPressed(const struct FGameplayTag& InputTag)
{
	InputPressedTags.Add(InputTag);
}

void UMyAbilitySystemComponent::AbilityInputTagReleased(const struct FGameplayTag& InputTag)
{
	unimplemented();
}

void UMyAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	AActor* MyOwner = GetOwner();
	for (const FGameplayTag& Tag : InputPressedTags)
	{
		FGameplayEventData Payload;
		Payload.EventTag    = Tag;
		Payload.Instigator  = MyOwner;
		Payload.Target      = MyOwner;
		int32 NumActivated = HandleGameplayEvent(Tag,&Payload);
		if (NumActivated == 0)
		{
			UE_LOG(LogAbilitySystemComponent,Warning,TEXT("Nothing Activated"));
		}
	}

	ClearAbilityInput();

}

void UMyAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedTags.Reset();
}

