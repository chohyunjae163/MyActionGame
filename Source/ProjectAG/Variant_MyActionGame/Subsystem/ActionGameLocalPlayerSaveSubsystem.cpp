// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameLocalPlayerSaveSubsystem.h"

#include "ActionGameGameplayTags.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interface/SaveParticipantInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameplayMessage/SaveMessage.h"
#include "SaveGame/MyLocalPlayerSaveGame.h"


void UActionGameLocalPlayerSaveSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
		
	MySaveGameObject = Cast<UMyLocalPlayerSaveGame>(ULocalPlayerSaveGame::LoadOrCreateSaveGameForLocalPlayer(
		UMyLocalPlayerSaveGame::StaticClass(),
		GetLocalPlayer(),
		MySlotName));
	
	if ( APlayerState* PS = NewPlayerController->GetPlayerState<APlayerState>(); IsValid(PS) ) 
	{
		TArray<UActorComponent*> ActorComponents = PS->GetComponentsByInterface(USaveParticipantInterface::StaticClass());
		for (UActorComponent* ActorComponent : ActorComponents)
		{
			ISaveParticipantInterface* SaveParticipant = Cast<ISaveParticipantInterface>(ActorComponent);
			SaveParticipant->ReadFromSave(MySaveGameObject);
		}
	}
	
}

void UActionGameLocalPlayerSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	MySlotName = TEXT("MyLocalPlayerSaveGame");
	MyUserIndex = 0;

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	SaveRequestListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::SaveEvent_Request,this,&ThisClass::OnRequestSave);
}

void UActionGameLocalPlayerSaveSubsystem::Deinitialize()
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(SaveRequestListenerHandle);
	
	Super::Deinitialize();
}

void UActionGameLocalPlayerSaveSubsystem::OnRequestSave(struct FGameplayTag Channel,
	const struct FRequestSaveMessage& Msg)
{
	ISaveParticipantInterface* SaveParticipant = Cast<ISaveParticipantInterface>(Msg.Requester);
	SaveParticipant->WriteToSave(MySaveGameObject);

	SaveGame(FAsyncSaveGameToSlotDelegate::CreateUObject(this,&ThisClass::OnSaveComplete));
}

void UActionGameLocalPlayerSaveSubsystem::OnSaveComplete(const FString& SlotName, const int32 SlotIndex, bool bSuccess)
{
	//
}


void UActionGameLocalPlayerSaveSubsystem::SaveGame(FAsyncSaveGameToSlotDelegate Callback) const
{
	UGameplayStatics::AsyncSaveGameToSlot(MySaveGameObject,MySlotName,0,Callback);
}
