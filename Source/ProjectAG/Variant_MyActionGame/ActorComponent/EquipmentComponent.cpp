// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "SaveGame/MyLocalPlayerSaveGame.h"


// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentComponent::WriteToSave(class USaveGame* SaveGameObject)
{
	//save my weaaaaapon!
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	LocalPlayerSaveGame->WeaponRecord.Level = MyWeapon.Level;
	LocalPlayerSaveGame->WeaponRecord.Id = MyWeapon.DataAssetId;
}

void UEquipmentComponent::ReadFromSave(class USaveGame* SaveGameObject)
{
	//load my weaaaaapon!

	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	MyWeapon.DataAssetId = LocalPlayerSaveGame->WeaponRecord.Id;
	MyWeapon.Level = LocalPlayerSaveGame->WeaponRecord.Level;
}
