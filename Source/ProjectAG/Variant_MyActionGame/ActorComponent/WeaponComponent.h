// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnComponent.h"
#include "Data/WeaponDefinition.h"
#include "WeaponComponent.generated.h"


/**
 * it applies gameplay effects to owner's ASC.
 */
UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UWeaponComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

private:
	void OnLoadWeaponData();

	
private:
	FWeaponInstance WeaponInstance;

};
