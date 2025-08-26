// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "ActionGamePlayerController.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class AActionGamePlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	AActionGamePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	/** Method called after processing input */
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

private:
	class AActionGamePlayerState* GetPlayerState() const;
	class UMyAbilitySystemComponent* GetMyASC() const;

private:
	UPROPERTY()
	TObjectPtr<class ULocalPlayerUIBridgeComponent> LocalPlayerUIBridge;
};
