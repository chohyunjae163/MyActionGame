// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/WeaponDefinition.h"
#include "Interface/SaveParticipantInterface.h"
#include "EquipmentComponent.generated.h"



UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Weapon = 0,
	Count,
};

/**
 * attaches to PlayerState
 * save and load current character equipments (weapons and armours)
 * the player state has this component
 */
UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEquipmentComponent : public UActorComponent, public ISaveParticipantInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	const FRuntimeEquipmentData& GetWeapon() const { return Equipments[static_cast<uint8>(EEquipmentType::Weapon)]; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ~ begin ISaveParticipant Interface
	virtual void WriteToSave(class USaveGame* SaveGameObject) override;
	virtual void ReadFromSave(class USaveGame* SaveGameObject) override;
	// ~ end ISaveParticipant Interface

private:
	void OnLoadEquipmentAsset(TSharedPtr<struct FStreamableHandle>);

#if WITH_EDITOR
	//find any attached weapon on character mesh on the blueprint and add it to Equipment[Weapon]
	void EDITOR_AddDefaultWeapon();
	void EDITOR_OnLoadAllWeapons();
#endif

private:
	TArray<FRuntimeEquipmentData> Equipments;

	

};
