// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLocalPlayerSaveGame.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameplayMessage/PlayerEventMessage.h"

void UMyLocalPlayerSaveGame::InitializeSaveGame(const ULocalPlayer* LocalPlayer, FString InSlotName, bool bWasLoaded)
{
	Super::InitializeSaveGame(LocalPlayer, InSlotName, bWasLoaded);

}


void UMyLocalPlayerSaveGame::UpdateInventory(TConstArrayView<FItemInstance> ItemList)
{
	ItemInstances = ItemList;
}

void UMyLocalPlayerSaveGame::OnInventoryUpdated(struct FGameplayTag Channel, const struct FPlayerInventoryUpdated& Msg)
{
	UpdateInventory(Msg.ItemList);

	//notify saving started
	AsyncSaveGameToSlotForLocalPlayer();
	
}

void UMyLocalPlayerSaveGame::HandlePostSave(bool bSuccess)
{
	Super::HandlePostSave(bSuccess);
	
	//notify saving ended
}
