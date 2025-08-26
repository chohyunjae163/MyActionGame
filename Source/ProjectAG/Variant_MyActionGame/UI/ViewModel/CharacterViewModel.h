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
	virtual void Initialize(class UAbilitySystemComponent* ASC);
	virtual void Deinitialize(class UAbilitySystemComponent* ASC) const;

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetHealthPercentage() const;
	
	UFUNCTION(BlueprintPure,FieldNotify)
	float GetMaxStamina() const;
	
	UFUNCTION(BlueprintPure,FieldNotify)
	float GetStaminaPercentage() const;

private:
	//stamina
	int32 GetHealth() const;
	void SetHealth(int32 NewHealth);
	void SetMaxHealth(int32 SetMaxHealth);
	
	//stamina
	int32 GetStamina() const;
	void SetStamina(int32 SetStamina);
	void SetMaxStamina(int32 SetMaxStamina);

	void OnHealthChanged(const struct FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const struct FOnAttributeChangeData& Data);
	void OnStaminaChanged(const struct FOnAttributeChangeData& Data);
	void OnMaxStaminaChanged(const struct FOnAttributeChangeData& Data);
	
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
