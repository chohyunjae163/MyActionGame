// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameBPFuncLib.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"

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
