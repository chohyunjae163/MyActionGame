// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameBPFuncLib.h"

#include "AbilitySystemComponent.h"
#include "ActorComponent/EquipmentComponent.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY(LogActionGameBPFuncLib)

class UAbilitySystemComponent* UActionGameBPFuncLib::GetAbilitySystemComponent(APawn* Pawn)
{
	// first try pawn
	{
		UAbilitySystemComponent* ASC = Pawn->FindComponentByClass<UAbilitySystemComponent>();
		if (IsValid(ASC))
		{
			return ASC;
		}		
	}


	//if it fails, then try player state
	APlayerState* PS = Pawn->GetPlayerState();

	if (IsValid(PS))
	{
		
		UAbilitySystemComponent* ASC = PS->FindComponentByClass<UAbilitySystemComponent>();
		if (IsValid(ASC))
		{
			return ASC;
		}
	}

	return nullptr;
}

void UActionGameBPFuncLib::GetCurrentWeapon(APawn* Pawn, struct FRuntimeEquipmentData& OutWeaponData)
{
	UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>();

	if (IsValid(EquipmentComponent))
	{
		OutWeaponData = EquipmentComponent->GetWeapon();	
	}
	else
	{
		UE_LOG(LogActionGameBPFuncLib,Warning,TEXT("Pawn %s has no Weapon"), *Pawn->GetName());
	}
}
