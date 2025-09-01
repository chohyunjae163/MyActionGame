// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI,Blueprintable,Const)
class UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UPaperSprite> Icon;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> Effects;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UAssignableActionBase> AssignableAction;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxQuantity;
};


USTRUCT()
struct FInventoryItemHandle
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid Guid; 

	bool IsValid() const { return Guid.IsValid(); }

	static FInventoryItemHandle NewHandle(FStringView ObjectPath)
	{
		FInventoryItemHandle H;
		H.Guid = FGuid::NewDeterministicGuid(ObjectPath);
		return H;
	}

	bool operator==(const FInventoryItemHandle& Other) const
	{
		return Guid == Other.Guid;
	}

};


//runtime item info
USTRUCT()
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY()
	FInventoryItemHandle Handle;
	
	UPROPERTY()
	FPrimaryAssetId ItemAssetId;

	UPROPERTY()
	int32 Quantity = 0;

	UPROPERTY()
	int32 QuickSlotIndex = INDEX_NONE;

	bool operator==(const FItemInstance& Other) const
	{
		return Handle == Other.Handle;
	}

	bool IsValid() const { return Handle.IsValid(); }
};