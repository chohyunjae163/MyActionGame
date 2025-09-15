// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionSubsystem.h"

#include "AbilitySystemComponent.h"
#include "ActionGameGameplayTags.h"
#include "Data/WeaponDefinition.h"
#include "GameplayAttribute/ActionGameCharacterAttributeSet.h"
#include "GameplayEffect/GameplayEffect_Damage.h"

void UDamageExecutionSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UDamageExecutionSubsystem::RequestDamage(class UAbilitySystemComponent* AttackerASC,
                                              class UAbilitySystemComponent* TargetASC,
                                              const class UWeaponDefinition* AttackerWeapon)
{
	const float WeaponDamage = AttackerWeapon->BaseDamage;
	const float CharacterStr = GetCharacterStr(AttackerASC);
	const float Damage = CalculateDamage(WeaponDamage,CharacterStr);
	ApplyDamageGE(AttackerASC,Damage);
}

float UDamageExecutionSubsystem::GetCharacterStr(class UAbilitySystemComponent* AttackerASC)
{
	if (IsValid(AttackerASC) == false)
	{
		return 0.0f;
	}
	const UActionGameCharacterAttributeSet* AttributeSet =
		Cast<UActionGameCharacterAttributeSet>(AttackerASC->GetAttributeSet(UActionGameCharacterAttributeSet::StaticClass()));
	if (IsValid(AttributeSet) == false)
	{
		return 0.0f;
	}
	return AttributeSet->GetStrength();
}

void UDamageExecutionSubsystem::ApplyDamageGE(const class UAbilitySystemComponent* AttackerASC, float InRawDamage)
{
	
	FGameplayEffectSpecHandle SpecHandle = AttackerASC->MakeOutgoingSpec(UGameplayEffect_Damage::StaticClass(),1,AttackerASC->MakeEffectContext());
	if (SpecHandle.Data.IsValid())
	{
		static FGameplayTag GameplayTag = ActionGameGameplayTags::SetByCaller_Damage;
		SpecHandle.Data->SetSetByCallerMagnitude(GameplayTag,InRawDamage);		
	}

}
