// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ActionGameLocalPlayerSaveSubsystem.generated.h"


enum class ESaveGameDataType : uint8
{
	Inventory,
};

/**
 * 
 */
UCLASS()
class PROJECTAG_API UActionGameLocalPlayerSaveSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	
	// ~ Begin USubsystem Interface
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;
	// ~ End USubsystem Interface

	/** Callback for when the player controller is changed on this subsystem's owning local player */
	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;
	
	void SaveGame(FAsyncSaveGameToSlotDelegate Callback) const;

private:
	void OnRequestSave(struct FGameplayTag Channel, const struct FRequestSaveMessage& Msg);
	void OnSaveComplete(const FString&, const int32, bool);
private:
	FString MySlotName;
	int32	MyUserIndex;

	UPROPERTY()
	TObjectPtr<class UMyLocalPlayerSaveGame> MySaveGameObject;

	FGameplayMessageListenerHandle SaveRequestListenerHandle;
};
