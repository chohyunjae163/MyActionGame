// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionGameGameMode.generated.h"

/**
 * The base game mode class used by this project.
 *  set up my playercontroller, playerstate and hud class in the constructor 
 */
UCLASS(MinimalAPI)
class AActionGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AActionGameGameMode(const FObjectInitializer& ObjectInitializer);
};
