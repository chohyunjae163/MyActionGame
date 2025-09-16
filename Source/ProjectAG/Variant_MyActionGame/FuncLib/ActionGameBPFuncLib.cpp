// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameBPFuncLib.h"

#include "AbilitySystemComponent.h"
#include "ActorComponent/EquipmentComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"

DEFINE_LOG_CATEGORY(LogActionGameBPFuncLib)

class UAbilitySystemComponent* UActionGameBPFuncLib::GetAbilitySystemComponent(APawn* Pawn)
{
	// first try pawn
	{
		UAbilitySystemComponent* ASC = Pawn->FindComponentByClass<UAbilitySystemComponent>();
		if (IsValid(ASC))
		{
			return ASC;
		}		
	}


	//if it fails, then try player state
	APlayerState* PS = Pawn->GetPlayerState();

	if (IsValid(PS))
	{
		
		UAbilitySystemComponent* ASC = PS->FindComponentByClass<UAbilitySystemComponent>();
		if (IsValid(ASC))
		{
			return ASC;
		}
	}

	return nullptr;
}

void UActionGameBPFuncLib::GetCurrentWeapon(APawn* Pawn, struct FRuntimeEquipmentData& OutWeaponData)
{
	
	UEquipmentComponent* EquipmentComponent = Pawn->FindComponentByClass<UEquipmentComponent>();
	if (IsValid(EquipmentComponent) == false)
	{
		APlayerState* PlayerState = Pawn->GetPlayerState();
		EquipmentComponent = PlayerState->FindComponentByClass<UEquipmentComponent>();
	}

	if (IsValid(EquipmentComponent))
	{
		OutWeaponData = EquipmentComponent->GetWeapon();	
	}
	else
	{
		UE_LOG(LogActionGameBPFuncLib,Warning,TEXT("Pawn %s has no Weapon"), *Pawn->GetName());
	}
}

TArray<TSoftObjectPtr<UAnimMontage>> UActionGameBPFuncLib::GetAttackMotionSet(APawn* Pawn)
{
	FRuntimeEquipmentData EquipmentData;
	GetCurrentWeapon(Pawn,EquipmentData);

	UObject* AssetObj = UAssetManager::Get().GetPrimaryAssetObject(EquipmentData.DataAssetId);
	UWeaponDefinition* WeaponDefinition = Cast<UWeaponDefinition>(AssetObj);
	return WeaponDefinition->MotionSet;
}

USkeletalMeshComponent* UActionGameBPFuncLib::GetMyCharacterMeshComp(UActorComponent* Self)
{
	if (IsValid(Self) == false)
	{
		return nullptr;
	}
	AActor* Owner = Self->GetOwner();
	if (IsValid(Owner) == false)
	{
		return nullptr;
	}

	if (ACharacter* Character = Cast<ACharacter>(Owner))
	{
		return Character->GetMesh();
	}

	if (APlayerState* PS = Cast<APlayerState>(Owner))
	{
		APawn* Pawn = PS->GetPawn();
		return Pawn->FindComponentByClass<USkeletalMeshComponent>();
	}

	if (APlayerController* PC = Cast<APlayerController>(Owner))
	{
		APawn* Pawn = PC->GetPawn();
		return Pawn->FindComponentByClass<USkeletalMeshComponent>();
	}

	return nullptr;
}
