// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionSubsystem.h"

#include "AbilitySystemComponent.h"
#include "ActionGameGameplayTags.h"
#include "Data/WeaponDefinition.h"
#include "Engine/AssetManager.h"
#include "FuncLib/ActionGameBPFuncLib.h"
#include "GameplayAttribute/ActionGameCharacterAttributeSet.h"
#include "GameplayEffect/GameplayEffect_Damage.h"

void UDamageExecutionSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UDamageExecutionSubsystem::RequestDamageExecution(class UAbilitySystemComponent* AttackerASC,
                                              class UAbilitySystemComponent* TargetASC)
{
	FRuntimeEquipmentData EquipmentData;
	APawn* AttackingPawn = Cast<APawn>(AttackerASC->GetAvatarActor());
	UActionGameBPFuncLib::GetCurrentWeapon(AttackingPawn,OUT EquipmentData);
	UWeaponDefinition* WeaponDefinition = Cast<UWeaponDefinition>(UAssetManager::Get().GetPrimaryAssetObject(EquipmentData.DataAssetId));
	
	const float WeaponDamage = WeaponDefinition->BaseDamage;
	const float CharacterStr = GetCharacterStr(AttackerASC);
	const float Damage = CalculateDamage(WeaponDamage,CharacterStr);

	// apply damage effect
	FGameplayEffectSpecHandle SpecHandle = AttackerASC->MakeOutgoingSpec(UGameplayEffect_Damage::StaticClass(),1,AttackerASC->MakeEffectContext());
	if (SpecHandle.Data.IsValid())
	{
		static FGameplayTag GameplayTag = ActionGameGameplayTags::SetByCaller_Damage;
		SpecHandle.Data->SetSetByCallerMagnitude(GameplayTag,Damage);
		TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
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
