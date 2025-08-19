// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "ActionGamePawnData.generated.h"




/**
 *  Definition of a pawn 
 */
UCLASS(MinimalAPI,Const)
class UActionGamePawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()


	// pawn blueprint
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PawnClass;

	// pawn's abilities
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> GrantedGameplayAbilities;
};
