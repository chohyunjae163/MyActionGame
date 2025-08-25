// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularPlayerState.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "ActionGamePlayerState.generated.h"

/**
 * for shared information about a specific player
 * The PlayerState is also replicated to everyone and can be used to retrieve and display data on other clients.
 * An easy way to access all PlayerStates is the PlayerArray inside the AGameState class.
 *
 * Create AbilitySystemComponent and AttributeSet.  attach them to PlayerState
 * init/deinit CharacterViewModel with AbilitySystemComponent
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

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	class UCharacterViewModel* GetCharacterViewModel() const;
	void OnSystemInitialized(struct FGameplayTag Channel, const struct FSystemInitializedMessage& Message);
private:
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY()
	TObjectPtr<class UMyAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UActionGameCharacterAttributeSet> PlayerAttributeSet;


	FGameplayMessageListenerHandle	ListenerHandle;
};
