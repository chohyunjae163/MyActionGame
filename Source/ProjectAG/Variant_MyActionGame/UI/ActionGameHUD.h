// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ActionGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API AActionGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
