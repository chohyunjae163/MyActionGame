#pragma once


#include "WeaponDefinition.generated.h"


UCLASS(MinimalAPI,Blueprintable,Const)
class UEquipmentDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UStaticMesh>> Meshes;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class UGameplayEffect>> Effects;

};

UCLASS(MinimalAPI,Blueprintable,Const)
class UWeaponDefinition : public UEquipmentDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UAnimMontage>> MotionSet;
	
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly)
	float Weight;
};

//runtime equipment info
USTRUCT()
struct FRuntimeEquipmentData
{
	GENERATED_BODY()
	
	UPROPERTY()
	FPrimaryAssetId DataAssetId;

	UPROPERTY()
	int32 CurrentDurability;

};