// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ItemEntryViewModel.generated.h"


/**
 * 
 */
UCLASS(MinimalAPI)
class UItemEntryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()


public:
	void OnEntryUpdate(TSoftObjectPtr<class UPaperSprite> SoftObject_PaperSprite, int32 Quantity);
	
	void Initialize(const FPrimaryAssetId& Id, int32 Quantity);
	UPROPERTY(BlueprintReadWrite,FieldNotify)
	TSoftObjectPtr<class UPaperSprite> SoftObj_PaperSprite;

	UPROPERTY(BlueprintReadWrite,FieldNotify)
	int32 Quantity;
	
};
