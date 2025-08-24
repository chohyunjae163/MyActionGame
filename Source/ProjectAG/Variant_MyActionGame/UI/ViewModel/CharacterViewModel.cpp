// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterViewModel.h"

int32 UCharacterViewModel::GetHealth() const
{
	return Health;
}

float UCharacterViewModel::GetMaxHealth() const
{
	return static_cast<float>(MaxHealth);
}

void UCharacterViewModel::SetHealth(int32 NewHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Health,NewHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercentage);
	}
}

void UCharacterViewModel::SetMaxHealth(int32 NewMaxHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth,NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxHealth);
	}
}

float UCharacterViewModel::GetHealthPercentage() const
{
	return Health / FMath::Max(MaxHealth,1);
}

int32 UCharacterViewModel::GetStamina() const
{
	return Stamina;
}

float UCharacterViewModel::GetMaxStamina() const
{
	return static_cast<float>(MaxStamina);
}

void UCharacterViewModel::SetStamina(int32 NewStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Stamina,NewStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Stamina);
	}
}

void UCharacterViewModel::SetMaxStamina(int32 NewMaxStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxStamina,NewMaxStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxStamina);
	}
}

float UCharacterViewModel::GetStaminaPercentage() const
{
	return Stamina / FMath::Max(MaxStamina,1);
}

