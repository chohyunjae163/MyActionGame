// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"

#include "ActionGameUIManagerSubsystem.generated.h"

/**
 * this class is required for UCommonGameInstance to work.
 * UGameUIManagerSubsystem is a part of CommonGame plugins
 *
 * @see int32 UCommonGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
 */
UCLASS(MinimalAPI)
class UActionGameUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()
	
};
