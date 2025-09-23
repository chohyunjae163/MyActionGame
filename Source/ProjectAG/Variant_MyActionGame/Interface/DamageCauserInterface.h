// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageCauserInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageCauserInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IDamageCauserInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TObjectPtr<APawn> GetDamageCauserPawn() const = 0;

	virtual class UAbilitySystemComponent* GetMyAbilitySystemComponent()  const = 0;
};
