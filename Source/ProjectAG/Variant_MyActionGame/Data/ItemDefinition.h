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
