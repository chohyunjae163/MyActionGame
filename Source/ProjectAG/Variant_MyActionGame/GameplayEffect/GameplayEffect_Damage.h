// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffect_Damage.generated.h"

/**
 * [WeaponDefinition + Instance + Stats] 
		  ↓ (계산)
	   RawDamage
		  ↓ (주입, SetByCaller)
   [GE_Damage SpecHandle]
		  ↓ (적용)
   [Target ASC → Execution → Health 감소]
 *
 * a universal effect for attack damage
 */
UCLASS()
class PROJECTAG_API UGameplayEffect_Damage : public UGameplayEffect
{
	GENERATED_BODY()
};
