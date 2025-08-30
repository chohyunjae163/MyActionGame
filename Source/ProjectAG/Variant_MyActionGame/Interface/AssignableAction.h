// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AssignableAction.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAssignableAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTAG_API IAssignableAction
{
	GENERATED_BODY()


public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void Execute(AActor* Instigator) = 0;
};

UCLASS(Abstract)
class UAssignableActionBase : public UObject, public IAssignableAction
{
	GENERATED_BODY()

	virtual void Execute(AActor* Instigator) override {}
};

UCLASS()
class UAssignableAction_ConsumeItem : public UAssignableActionBase
{
	GENERATED_BODY()

	
	virtual void Execute(AActor* Instigator) override {}
};
