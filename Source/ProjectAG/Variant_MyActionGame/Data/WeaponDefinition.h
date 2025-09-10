#pragma once


#include "WeaponDefinition.generated.h"


UCLASS(MinimalAPI,Blueprintable,Const)
class UWeaponDefinition : public UPrimaryDataAsset
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

//runtime weapon info
USTRUCT()
struct FWeaponInstance
{
	GENERATED_BODY()
	
	UPROPERTY()
	FPrimaryAssetId DataAssetId;

	UPROPERTY()
	int32 Level;

};