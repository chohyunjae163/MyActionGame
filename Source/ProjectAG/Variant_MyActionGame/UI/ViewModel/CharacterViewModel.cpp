// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterViewModel.h"

#include "AbilitySystemComponent.h"
#include "Variant_MyActionGame/GameplayAttribute/ActionGameCharacterAttributeSet.h"

void UCharacterViewModel::Initialize(class UAbilitySystemComponent* ASC)
{
	if (IsValid(ASC))
	{
		const UActionGameCharacterAttributeSet* Attributes = ASC->GetSet<UActionGameCharacterAttributeSet>();
		if (!IsValid(Attributes))
		{
			return;
		}
		
		UE_MVVM_SET_PROPERTY_VALUE(Health,     Attributes->GetHealth());
		UE_MVVM_SET_PROPERTY_VALUE(MaxHealth,  Attributes->GetMaxHealth());
		UE_MVVM_SET_PROPERTY_VALUE(Stamina,    Attributes->GetStamina());
		UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, Attributes->GetMaxStamina());
		
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).AddUObject(this,&ThisClass::OnMaxHealthChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetStaminaAttribute()).AddUObject(this,&ThisClass::OnStaminaChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxStaminaAttribute()).AddUObject(this,&ThisClass::OnMaxStaminaChanged);

	}
}

void UCharacterViewModel::Deinitialize(class UAbilitySystemComponent* ASC) const
{
	if (IsValid(ASC))
	{
		const UActionGameCharacterAttributeSet* Attributes = ASC->GetSet<UActionGameCharacterAttributeSet>();
		if (!IsValid(Attributes))
		{
			return;
		}
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxHealthAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetStaminaAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(Attributes->GetMaxStaminaAttribute()).RemoveAll(this);
		
	}
}

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

void UCharacterViewModel::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	SetHealth(Data.NewValue);
}

void UCharacterViewModel::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	SetMaxHealth(Data.NewValue);	
}

void UCharacterViewModel::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	SetStamina(Data.NewValue);
}

void UCharacterViewModel::OnMaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	SetMaxStamina(Data.NewValue);
}

