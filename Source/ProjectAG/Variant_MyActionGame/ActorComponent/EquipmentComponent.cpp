// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "SaveGame/MyLocalPlayerSaveGame.h"


static constexpr uint8 GetWeaponIndex() { return static_cast<uint8>(EEquipmentType::Weapon); }
static constexpr uint8 WEAPON_INDEX = GetWeaponIndex();


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
	Equipments.SetNum(static_cast<uint8>(EEquipmentType::Count));

	TArray<FPrimaryAssetId> AssetsToLoad;
	AssetsToLoad.Reserve(Equipments.Num());
	Algo::Transform(Equipments,AssetsToLoad,
		[] (const FRuntimeEquipmentData& Data){ return Data.DataAssetId; });

	TArray<FName> LoadBundles;
	FAssetManagerLoadParams Params;
	Params.OnComplete.BindUObject(this,&ThisClass::OnLoadEquipmentAsset);
	UAssetManager::Get().LoadPrimaryAssets(AssetsToLoad,LoadBundles,MoveTemp(Params));
}

void UEquipmentComponent::WriteToSave(class USaveGame* SaveGameObject)
{
	const FRuntimeEquipmentData& MyWeapon = Equipments[WEAPON_INDEX];
	//save my weaaaaapon!
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	LocalPlayerSaveGame->WeaponRecord.Durability = MyWeapon.CurrentDurability;
	LocalPlayerSaveGame->WeaponRecord.Id = MyWeapon.DataAssetId;
}

void UEquipmentComponent::ReadFromSave(class USaveGame* SaveGameObject)
{
	//load my weaaaaapon!
	FRuntimeEquipmentData& MyWeapon = Equipments[WEAPON_INDEX];
	
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	MyWeapon.DataAssetId = LocalPlayerSaveGame->WeaponRecord.Id;
	MyWeapon.CurrentDurability = LocalPlayerSaveGame->WeaponRecord.Durability;
}

void UEquipmentComponent::OnLoadEquipmentAsset(TSharedPtr<struct FStreamableHandle> Handle)
{
	//todo: notify all equipment data is loaded
}
