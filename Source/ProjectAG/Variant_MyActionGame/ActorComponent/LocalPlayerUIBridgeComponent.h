// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "LocalPlayerUIBridgeComponent.generated.h"


/**
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
	ULocalPlayerUIBridgeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnInteractableFound(struct FGameplayTag Channel, const struct FWorldInteractionMessage& Msg);
private:
	FGameplayMessageListenerHandle	ListenerHandle;
};
