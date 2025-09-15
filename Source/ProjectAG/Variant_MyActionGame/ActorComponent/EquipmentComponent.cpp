// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "FuncLib/ActionGameBPFuncLib.h"
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

	// check to see if a controlled pawn has a weapon attached
#if WITH_EDITOR
	EDITOR_AddDefaultWeapon();
#endif
	
	if (Equipments.IsEmpty() == false)
	{
		TArray<FPrimaryAssetId> AssetsToLoad;
		AssetsToLoad.Reserve(Equipments.Num());
		Algo::Transform(Equipments,AssetsToLoad,
			[] (const FRuntimeEquipmentData& Data){ return Data.DataAssetId; });

		TArray<FName> LoadBundles;
		FAssetManagerLoadParams Params;
		Params.OnComplete.BindUObject(this,&ThisClass::OnLoadEquipmentAsset);
		UAssetManager::Get().LoadPrimaryAssets(AssetsToLoad,LoadBundles,MoveTemp(Params));	
	}

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
	//load my weapon record!
	
	UMyLocalPlayerSaveGame* LocalPlayerSaveGame = Cast<UMyLocalPlayerSaveGame>(SaveGameObject);
	FWeaponRecord& WeaponRecord = LocalPlayerSaveGame->WeaponRecord;
	if (WeaponRecord.Id.IsValid())
	{
		FRuntimeEquipmentData EquipmentData;
		EquipmentData.DataAssetId = LocalPlayerSaveGame->WeaponRecord.Id;
		EquipmentData.CurrentDurability = LocalPlayerSaveGame->WeaponRecord.Durability;
		Equipments[WEAPON_INDEX] = EquipmentData;
	}

}

void UEquipmentComponent::OnLoadEquipmentAsset(TSharedPtr<struct FStreamableHandle> Handle)
{
	//todo: notify all equipment data is loaded
}

#if WITH_EDITOR
void UEquipmentComponent::EDITOR_AddDefaultWeapon()
{

	TArray<FName> LoadBundles;
	UAssetManager::Get().LoadPrimaryAssetsWithType(TEXT
		("WeaponDefinition"),
		LoadBundles,
		FStreamableDelegate::CreateUObject(this,&UEquipmentComponent::EDITOR_OnLoadAllWeapons));

}

void UEquipmentComponent::EDITOR_OnLoadAllWeapons()
{
	TArray<UObject*> Objects;
	UAssetManager::Get().GetPrimaryAssetObjectList(TEXT("WeaponDefinition"),Objects);
	USkeletalMeshComponent* SkeletalMeshComponent = UActionGameBPFuncLib::GetMyCharacterMeshComp(this);
	UStaticMeshComponent* Weapon = Cast<UStaticMeshComponent>(SkeletalMeshComponent->GetChildComponent(0));
	for (UObject* Object : Objects)
	{
		if (UWeaponDefinition* WeaponDefinition = Cast<UWeaponDefinition>(Object))
		{
			for (auto WeaponMesh : WeaponDefinition->Meshes)
			{
				if (Weapon->GetStaticMesh() == WeaponMesh.Get())
				{
					FPrimaryAssetId Id = UAssetManager::Get().GetPrimaryAssetIdForObject(Object);
					FRuntimeEquipmentData EquipmentData;
					EquipmentData.CurrentDurability = 100;
					EquipmentData.DataAssetId = Id;
					Equipments.Emplace(EquipmentData);
					break;
				}
			}
		}
	}
}
#endif