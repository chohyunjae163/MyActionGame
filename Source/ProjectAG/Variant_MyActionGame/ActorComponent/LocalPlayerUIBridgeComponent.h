// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "LocalPlayerUIBridgeComponent.generated.h"


/**
 * attaches to Player Controller
 * this component bridges between UI System and Game World
 * if something happens and data changes, this will tell UI
 * to update
 */
UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ULocalPlayerUIBridgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULocalPlayerUIBridgeComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	[[nodiscard]] class UPlayerViewModel* GetPlayerViewModel() const;
	void OnPawnGameReady(struct FGameplayTag Channel, const struct FPawnGameReadyMessage& Message);

private:
	FGameplayMessageListenerHandle	ListenerHandle;
};
