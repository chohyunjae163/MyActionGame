// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameFramework/HUD.h"
#include "Types/MVVMViewModelContext.h"
#include "ActionGameHUD.generated.h"

/**
 * My HUD Actor.
 * add a character view model instance.
 * it listens the ability system initialization for the attributes setup in the viewmodel mentioned above.
 */
UCLASS()
class AActionGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	class UCharacterViewModel* GetCharacterViewModel() const;
	void OnSystemInitialized(struct FGameplayTag Channel, const struct FSystemInitializedMessage& Message);


private:
	FMVVMViewModelContext			Context;
	FGameplayMessageListenerHandle	ListenerHandle;
};
