// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Interact.h"
#include "GA_Interact_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UGA_Interact_Pickup : public UGA_Interact
{
	GENERATED_BODY()


private:
	virtual void OnMontageFinished() override;
};
