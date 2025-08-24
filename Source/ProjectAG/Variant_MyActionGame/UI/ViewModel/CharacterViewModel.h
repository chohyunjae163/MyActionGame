// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "CharacterViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCharacterViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	
	//stamina
	int32 GetHealth() const;
	void SetHealth(int32 NewHealth);

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetMaxHealth() const;
	void SetMaxHealth(int32 SetMaxHealth);

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetHealthPercentage() const;

	//stamina
	int32 GetStamina() const;
	void SetStamina(int32 SetStamina);

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetMaxStamina() const;
	void SetMaxStamina(int32 SetMaxStamina);

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetStaminaPercentage() const;

private:
	UPROPERTY(FieldNotify)
	int32 Health;

	UPROPERTY(FieldNotify)
	int32 MaxHealth;

	UPROPERTY(FieldNotify)
	int32 Stamina;

	UPROPERTY(FieldNotify)
	int32 MaxStamina;
	
};
