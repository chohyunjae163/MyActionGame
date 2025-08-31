// Fill out your copyright notice in the Description page of Project Settings.


#include "AssignableAction_Consumable.h"

#include "AbilitySystemComponent.h"
#include "ActionGameGameplayTags.h"


void UAssignableAction_Consumable::Execute(APawn* Instigator, class UAbilitySystemComponent* ASC)
{
	FGameplayEventData GameplayEventData;
	GameplayEventData.EventTag = ActionGameGameplayTags::CharacterEvent_UseConsumable;
	GameplayEventData.Instigator = Instigator;
	GameplayEventData.Target = Instigator;
	ASC->HandleGameplayEvent(
		ActionGameGameplayTags::CharacterEvent_UseConsumable,
		&GameplayEventData);

	
}
