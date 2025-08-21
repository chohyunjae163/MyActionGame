// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "Engine/GameInstance.h"
#include "ActionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UActionGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;
};
