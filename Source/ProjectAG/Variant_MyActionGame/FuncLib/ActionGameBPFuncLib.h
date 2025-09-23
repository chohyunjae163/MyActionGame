// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/WeaponDefinition.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionGameBPFuncLib.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogActionGameBPFuncLib, Log, All);

/**
 * 
 */
UCLASS(MinimalAPI)
class UActionGameBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static void GetCurrentWeapon(APawn* Pawn, FRuntimeEquipmentData& OutWeaponData);

	
	static USkeletalMeshComponent* GetMyCharacterMeshComp(UActorComponent* Self);
	static class UAbilitySystemComponent* GetAbilitySystemComponent(APawn* Pawn);
	static TArray<TSoftObjectPtr<UAnimMontage>> GetAttackMotionSet(APawn* Pawn);
	

};
