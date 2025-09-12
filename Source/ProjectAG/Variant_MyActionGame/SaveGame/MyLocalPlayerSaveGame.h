// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDefinition.h"
#include "GameFramework/SaveGame.h"
#include "MyLocalPlayerSaveGame.generated.h"


struct FItemRecord
{
	FPrimaryAssetId Id;
	int32 Quantity;

	FItemRecord() = default;
	FItemRecord(FPrimaryAssetId InId, int32 InQuantity):
		Id(InId),Quantity(InQuantity)
	{
		
	}
};

struct FWeaponRecord
{
	FPrimaryAssetId Id;
	int32 Durability;

	FWeaponRecord() = default;
	FWeaponRecord(FPrimaryAssetId InId, int32 InDurability):
		Id(InId),Durability(InDurability)
	{
		
	}
};

/**
 * 
 */
UCLASS(MinimalAPI)
class UMyLocalPlayerSaveGame : public ULocalPlayerSaveGame
{
	GENERATED_BODY()


public:
	virtual void InitializeSaveGame(const ULocalPlayer* LocalPlayer, FString InSlotName, bool bWasLoaded) override;
	//Called after saving finishes with success/failure result
	virtual void HandlePostSave(bool bSuccess) override; 

	void UpdateInventory(TConstArrayView<FItemInstance> ItemData);

	TArray<FItemRecord> ItemRecords;
	FWeaponRecord WeaponRecord;
private:
	void OnInventoryUpdated(struct FGameplayTag Channel, const struct FPlayerInventoryUpdated& Msg );
private:
	
};
