// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Extensions/UserWidgetExtension.h"
#include "QuickSlotBar_Viewmodel_Extension.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UQuickSlotBar_Viewmodel_Extension : public UUserWidgetExtension
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Items", ViewmodelBlueprintWidgetExtension = "EntryViewModel"))
	void SetItems(const TArray<class UItemEntryViewModel*>& InItems);
};
