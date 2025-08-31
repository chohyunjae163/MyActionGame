// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AssignableActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAssignableActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTAG_API IAssignableActionInterface
{
	GENERATED_BODY()


public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void Execute(APawn* Instigator, class UAbilitySystemComponent* ASC) = 0;
};