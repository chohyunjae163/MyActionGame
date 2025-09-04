// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameLocalPlayerSaveSubsystem.h"

#include "Interface/SaveParticipantInterface.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MyLocalPlayerSaveGame.h"

void UActionGameLocalPlayerSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	MySlotName = TEXT("MyLocalPlayerSaveGame");
	MyUserIndex = 0;

}

void UActionGameLocalPlayerSaveSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UActionGameLocalPlayerSaveSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
		
	MySaveGameObject = Cast<UMyLocalPlayerSaveGame>(ULocalPlayerSaveGame::LoadOrCreateSaveGameForLocalPlayer(
		UMyLocalPlayerSaveGame::StaticClass(),
		GetLocalPlayer(),
		MySlotName));
	
	if (APawn* MyPawn = NewPlayerController->GetPawn();IsValid(MyPawn))
	{
		TArray<UActorComponent*> ActorComponents = MyPawn->GetComponentsByInterface(USaveParticipantInterface::StaticClass());
		for (UActorComponent* ActorComponent : ActorComponents)
		{
			ISaveParticipantInterface* SaveParticipant = Cast<ISaveParticipantInterface>(ActorComponent);
			SaveParticipant->ReadFromSave(MySaveGameObject);
		}
	}
}

void UActionGameLocalPlayerSaveSubsystem::SaveGame(FAsyncSaveGameToSlotDelegate Callback) const
{
	UGameplayStatics::AsyncSaveGameToSlot(MySaveGameObject,MySlotName,0,Callback);
}
