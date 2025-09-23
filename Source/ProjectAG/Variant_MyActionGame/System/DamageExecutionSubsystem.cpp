// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionSubsystem.h"

#include "AbilitySystemComponent.h"
#include "ActionGameGameplayTags.h"
#include "Data/WeaponDefinition.h"
#include "Engine/AssetManager.h"
#include "FuncLib/ActionGameBPFuncLib.h"
#include "GameplayAttribute/ActionGameCharacterAttributeSet.h"
#include "GameplayEffect/GameplayEffect_Damage.h"
#include "Interface/DamageCauserInterface.h"

void UDamageExecutionSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UDamageExecutionSubsystem::RequestDamageExecution(class IDamageCauserInterface* DamageCauser,
                                              class UAbilitySystemComponent* TargetASC)
{
	APawn* AttackingPawn = DamageCauser->GetDamageCauserPawn();
	if (IsValid(AttackingPawn))
	{
		UAbilitySystemComponent* AttackerASC = DamageCauser->GetMyAbilitySystemComponent();
		FGameplayEffectSpecHandle SpecHandle = AttackerASC->MakeOutgoingSpec(UGameplayEffect_Damage::StaticClass(),1,AttackerASC->MakeEffectContext());
		if (SpecHandle.Data.IsValid())
		{
			static FGameplayTag GameplayTag = ActionGameGameplayTags::SetByCaller_Damage;
			FRuntimeEquipmentData EquipmentData;
			UActionGameBPFuncLib::GetCurrentWeapon(AttackingPawn,OUT EquipmentData);
			UWeaponDefinition* WeaponDefinition = Cast<UWeaponDefinition>(UAssetManager::Get().GetPrimaryAssetObject(EquipmentData.DataAssetId));
			const float WeaponBaseDamage = WeaponDefinition->BaseDamage;
			const UActionGameCharacterAttributeSet* CharacterAttributes = Cast<UActionGameCharacterAttributeSet>(AttackerASC->GetAttributeSet(UActionGameCharacterAttributeSet::StaticClass()));
			const float TotalDamage = CalculateDamage(CharacterAttributes,WeaponBaseDamage);
			SpecHandle.Data->SetSetByCallerMagnitude(GameplayTag,TotalDamage);
			TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

float UDamageExecutionSubsystem::CalculateDamage_Implementation(const UActionGameCharacterAttributeSet* CharacterAttributes,float WeaponDamage)
{
	//should be overriden by its blueprint
	return 0.0f;
}
