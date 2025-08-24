// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameGameMode.h"

#include "Player/ActionGamePlayerController.h"
#include "Player/ActionGamePlayerState.h"
#include "UI/ActionGameHUD.h"

AActionGameGameMode::AActionGameGameMode(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	PlayerControllerClass = AActionGamePlayerController::StaticClass();
	PlayerStateClass = AActionGamePlayerState::StaticClass();
	HUDClass = AActionGameHUD::StaticClass();
}
