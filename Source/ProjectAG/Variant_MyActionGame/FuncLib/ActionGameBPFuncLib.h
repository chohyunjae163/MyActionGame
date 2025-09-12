// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	static class UAbilitySystemComponent* GetAbilitySystemComponent(APawn* Pawn);
	static void GetCurrentWeapon(APawn* Pawn, OUT struct FRuntimeEquipmentData& OutWeaponData);
};
