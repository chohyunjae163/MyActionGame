// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryViewModel.h"

#include "Data/ItemDefinition.h"
#include "Engine/AssetManager.h"


void UItemEntryViewModel::Initialize(const FPrimaryAssetId& InId, int32 InQuantity)
{
	UItemDefinition* ItemDef = Cast<UItemDefinition>(UAssetManager::Get().GetPrimaryAssetObject(InId));
	if (IsValid(ItemDef)) //loaded
	{
		OnEntryUpdate(ItemDef->Icon,InQuantity);
	}
	else
	{
		//not loaded yet
		TArray<FName> LoadBundles;
		UAssetManager::Get().LoadPrimaryAsset(InId,LoadBundles,FStreamableDelegate::CreateLambda([WeakThis=MakeWeakObjectPtr(this),InId,InQuantity
			]()
		{
			if (WeakThis.IsValid())
			{
				UItemDefinition* ItemDef = Cast<UItemDefinition>(UAssetManager::Get().GetPrimaryAssetObject(InId));
				if (IsValid(ItemDef)) //loaded
				{
					WeakThis.Pin()->OnEntryUpdate(ItemDef->Icon,InQuantity);
				}
			}
		}));
	}
	
}

void UItemEntryViewModel::OnEntryUpdate(TSoftObjectPtr<class UPaperSprite> NewPaperSprite, int32 InQuantity)
{
	UE_MVVM_SET_PROPERTY_VALUE(SoftObj_PaperSprite,NewPaperSprite);
	UE_MVVM_SET_PROPERTY_VALUE(Quantity,InQuantity);
}
