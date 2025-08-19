// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularPlayerState.h"
#include "ActionGamePlayerState.generated.h"

/**
 * for shared information about a specific player
 * The PlayerState is also replicated to everyone and can be used to retrieve and display data on other clients.
 * An easy way to access all PlayerStates is the PlayerArray inside the AGameState class.
 */
UCLASS(MinimalAPI)
class AActionGamePlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	AActionGamePlayerState(const FObjectInitializer& ObjectInitializer);
	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
private:
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY()
	TObjectPtr<class UMyAbilitySystemComponent> AbilitySystemComponent;
};
