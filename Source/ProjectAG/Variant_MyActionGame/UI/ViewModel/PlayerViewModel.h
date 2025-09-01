// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterViewModel.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "PlayerViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UPlayerViewModel : public UCharacterViewModel
{
	GENERATED_BODY()

public:
	virtual void Initialize(class UAbilitySystemComponent* ASC) override;
	virtual void Deinitialize(class UAbilitySystemComponent* ASC) const override;


private:
	void OnInteractableFound(struct FGameplayTag Channel, const struct FWorldInteractionMessage& Msg);


private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess=true))
	bool bInteractable;
	
	FGameplayMessageListenerHandle	ListenerHandle;
};
