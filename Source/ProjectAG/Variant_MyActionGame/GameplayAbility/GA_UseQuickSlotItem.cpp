// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_UseQuickSlotItem.h"

void UGA_UseQuickSlotItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	//play a montage

	// Use Item?

	//inventorycomponent->useitem()?
	//
}
