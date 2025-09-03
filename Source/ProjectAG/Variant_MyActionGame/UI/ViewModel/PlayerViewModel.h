// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterViewModel.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "UI/ViewData.h"
#include "PlayerViewModel.generated.h"



/**
 * 
 */
UCLASS(MinimalAPI,BlueprintType)
class UPlayerViewModel : public UCharacterViewModel
{
	GENERATED_BODY()

public:
	virtual void Initialize(class AActionGamePlayerState* PlayerState);
	virtual void Deinitialize() const override;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	TArray<FItemViewData> GetQuickSlotItems() const;

private:
	void OnInteractableFound(struct FGameplayTag Channel, const struct FWorldInteractionMessage& Msg);
	void OnUseConsumable(struct FGameplayTag Channel, const struct FCharacterConsumableMessage& Msg);
	void OnQuickSlotItemChanged(int32 Index);
	
private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	bool bInteractable;

	TArray<FItemViewData> QuickSlotItemData;

	
	//퀵슬롯 아이템 개수와 아이콘 이미지를 표시해야한다
	//quick
	
	TArray<FGameplayMessageListenerHandle>	ListenerHandles;
	
};
