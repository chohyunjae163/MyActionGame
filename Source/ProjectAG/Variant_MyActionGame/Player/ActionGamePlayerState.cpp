// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerState.h"
#include "AbilitySystemComponent.h"
#include "Variant_MyActionGame/ActorComponent/MyAbilitySystemComponent.h"


AActionGamePlayerState::AActionGamePlayerState(const FObjectInitializer& ObjectInitializer)
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//...
}

UAbilitySystemComponent* AActionGamePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


