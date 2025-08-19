// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "ActionGamePawnData.generated.h"




/**
 * ULyraAbilitySet
 *
 *	Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(BlueprintType, Const)
class UActionGameAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UActionGameAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent);
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> GrantedGameplayAbilities;
};

/**
 *  Definition of a pawn 
 */
UCLASS(MinimalAPI,Const)
class UActionGamePawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UActionGameAbilitySet> AbilitySet;
};
