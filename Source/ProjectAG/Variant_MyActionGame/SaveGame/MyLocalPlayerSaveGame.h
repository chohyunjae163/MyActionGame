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

	FItemRecord(FPrimaryAssetId NewId, int32 NewQuantity):
		Id(NewId),Quantity(NewQuantity)
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
private:
	void OnInventoryUpdated(struct FGameplayTag Channel, const struct FPlayerInventoryUpdated& Msg );
private:
	
	TArray<struct FItemInstance> ItemInstances;


	
};
