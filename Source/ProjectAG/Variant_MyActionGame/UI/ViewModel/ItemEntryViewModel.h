// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "ItemEntryViewModel.generated.h"


/**
 * 
 */
UCLASS(MinimalAPI)
class UItemEntryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void Initialize(const FPrimaryAssetId& Id, int32 Quantity);
	
	void OnEntryUpdate(TSoftObjectPtr<class UPaperSprite> SoftObject_PaperSprite, int32 Quantity);
	
	UPROPERTY(BlueprintReadWrite,FieldNotify)
	TSoftObjectPtr<class UPaperSprite> SoftObj_PaperSprite;

	UPROPERTY(BlueprintReadWrite,FieldNotify)
	int32 Quantity;

private:
	void OnUseConsumable(struct FGameplayTag Channel, const struct FCharacterConsumableMessage& Msg);

private:
	int32 MyIndex;

	FGameplayMessageListenerHandle ListenerHandle;
};
