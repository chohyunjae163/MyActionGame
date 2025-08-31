// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssignableActionBase.h"
#include "AssignableAction_Consumable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UAssignableAction_Consumable : public UAssignableActionBase
{
	GENERATED_BODY()

	virtual void Execute(APawn* Instigator, class UAbilitySystemComponent* ASC) override;
};
