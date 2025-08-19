// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerController.h"

#include "ActionGamePlayerState.h"
#include "Variant_MyActionGame/ActorComponent/MyAbilitySystemComponent.h"



class AActionGamePlayerState* AActionGamePlayerController::GetPlayerState() const
{
	return CastChecked<AActionGamePlayerState>(PlayerState,ECastCheckedType::NullAllowed);
}


class UMyAbilitySystemComponent* AActionGamePlayerController::GetMyASC() const
{
	AActionGamePlayerState* MyPlayerState = GetPlayerState();
	return CastChecked<UMyAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent(),ECastCheckedType::NullAllowed);
}


void AActionGamePlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UMyAbilitySystemComponent* MyASC = GetMyASC())
	{
		MyASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

