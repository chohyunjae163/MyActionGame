// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerController.h"
#include "ActionGamePlayerController.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class AActionGamePlayerController : public AModularPlayerController
{
	GENERATED_BODY()


protected:
	/** Method called after processing input */
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

private:
	class AActionGamePlayerState* GetPlayerState() const;
	class UMyAbilitySystemComponent* GetMyASC() const;
};
