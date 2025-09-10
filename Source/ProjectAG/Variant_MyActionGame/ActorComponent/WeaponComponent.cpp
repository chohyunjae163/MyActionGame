// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "AbilitySystemComponent.h"
#include "Data/WeaponDefinition.h"
#include "Engine/AssetManager.h"
#include "GameFramework/PlayerState.h"

UWeaponComponent::UWeaponComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//todo: where should i get the weaponinstance from?

	TArray<FName> LoadBundles;
	UAssetManager::Get().LoadPrimaryAsset(
		WeaponInstance.DataAssetId,
		LoadBundles,
		FStreamableDelegate::CreateUObject(this,&ThisClass::OnLoadWeaponData));
}

void UWeaponComponent::OnLoadWeaponData()
{
	UWeaponDefinition* WeaponDef = Cast<UWeaponDefinition>(UAssetManager::Get().GetPrimaryAssetObject(WeaponInstance.DataAssetId));
	if (IsValid(WeaponDef))
	{
		UAbilitySystemComponent* ASC = GetPlayerState<APlayerState>()->FindComponentByClass<UAbilitySystemComponent>();
		if (IsValid(ASC))
		{
			for (TSubclassOf GameplayEffectClass : WeaponDef->Effects)
			{
				FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
				const int32 Level = WeaponInstance.Level;
				FGameplayEffectSpecHandle SpecHandle = 	ASC->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
				UGameplayEffect* GameplayEffect = GameplayEffectClass->GetDefaultObject<UGameplayEffect>();
				ASC->ApplyGameplayEffectToSelf(GameplayEffect,Level,ContextHandle);
			}
		}		
	}
	
}
