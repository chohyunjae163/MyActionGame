// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ActionGameCharacter.generated.h"

UCLASS(MinimalAPI,Blueprintable)
class AActionGameCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionGameCharacter();

protected:

	// any action game character needs this.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UActionGamePawnComponent> ActionGamePawnComponent;
	
};
