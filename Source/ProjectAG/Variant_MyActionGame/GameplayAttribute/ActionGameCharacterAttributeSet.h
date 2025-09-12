// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ActionGameCharacterAttributeSet.generated.h"


/*
 * GAS AttributeSet Unreal Documentation
 * https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-attributes-and-attribute-sets-for-the-gameplay-ability-system-in-unreal-engine
 */

/**
 * 
 */
UCLASS(MinimalAPI)
class UActionGameCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


	// HEALTH
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	//~ Helper functions for "Health" attributes
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UActionGameCharacterAttributeSet, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UActionGameCharacterAttributeSet, MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);

	// Stamina
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxStamina;
	
	//~ Helper functions for "Stamina" attributes
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UActionGameCharacterAttributeSet, Stamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Stamina);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UActionGameCharacterAttributeSet, MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxStamina);

	//Strength
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Strength;
	
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UActionGameCharacterAttributeSet, Strength);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Strength);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Strength);
};
