// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameInstance.h"

#include "ActionGameGameplayTags.h"
#include "Components/GameFrameworkComponentManager.h"

void UActionGameInstance::Init()
{
	Super::Init();

	// Register our custom init states
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);

	if (ensure(ComponentManager))
	{
		ComponentManager->RegisterInitState(ActionGameGameplayTags::InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(ActionGameGameplayTags::InitState_DataAvailable, false, ActionGameGameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(ActionGameGameplayTags::InitState_DataInitialized, false, ActionGameGameplayTags::InitState_DataAvailable);
		ComponentManager->RegisterInitState(ActionGameGameplayTags::InitState_GameplayReady, false, ActionGameGameplayTags::InitState_DataInitialized);
	}
}
