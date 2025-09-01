// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerState.h"
#include "AbilitySystemComponent.h"
#include "Variant_MyActionGame/ActorComponent/MyAbilitySystemComponent.h"
#include "Variant_MyActionGame/GameplayAttribute/ActionGameCharacterAttributeSet.h"



class UMVVMGameSubsystem;

AActionGamePlayerState::AActionGamePlayerState(const FObjectInitializer& ObjectInitializer)
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//...

	PlayerAttributeSet = CreateDefaultSubobject<UActionGameCharacterAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* AActionGamePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TConstArrayView<FQuickSlotAssignment> AActionGamePlayerState::ViewQuickSlot() const
{
	return QuickSlotItems;
}