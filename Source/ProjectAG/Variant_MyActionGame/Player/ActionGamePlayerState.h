// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularPlayerState.h"
#include "Data/ActionGameConsts.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "ActionGamePlayerState.generated.h"




USTRUCT(BlueprintType)
struct FQuickSlotData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FPrimaryAssetId ItemAssetId;

	UPROPERTY(BlueprintReadWrite)
	int32 Quantity;
};

/**
 * for shared information about a specific player
 * The PlayerState is also replicated to everyone and can be used to retrieve and display data on other clients.
 * An easy way to access all PlayerStates is the PlayerArray inside the AGameState class.
 *
 * Create AbilitySystemComponent and AttributeSet.  attach them to the PlayerState
 */
UCLASS(MinimalAPI,Blueprintable)
class AActionGamePlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	AActionGamePlayerState(const FObjectInitializer& ObjectInitializer);

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	UFUNCTION(BlueprintPure)
	TArray<FQuickSlotData> ViewQuickSlot() const;
	void OnQuickSlotItemChanged(struct FGameplayTag Channel, const struct FUI_QuickSlotChangedMessage& Message);


private:
	void TempTestData();

protected:
	UPROPERTY(EditAnywhere)
	FPrimaryAssetId DallaeAssetId;
private:
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY()
	TObjectPtr<class UMyAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UActionGameCharacterAttributeSet> PlayerAttributeSet;

	TStaticArray<FQuickSlotData, NUM_QUICK_SLOT>	QuickSlotItems;
	FGameplayMessageListenerHandle					QuickSlotChangeListenerHandle;
};
