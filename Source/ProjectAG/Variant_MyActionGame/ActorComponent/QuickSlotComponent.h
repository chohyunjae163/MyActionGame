// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Interface/AssignableActionInterface.h"
#include "QuickSlotComponent.generated.h"

USTRUCT()
struct FQuickSlot
{
	GENERATED_BODY()
	
	TSubclassOf<IAssignableActionInterface> ActionClass;

	UPROPERTY(Transient)
	TObjectPtr<UObject> ActionInstance;
};

USTRUCT()
struct FQuickSlotBar
{
	GENERATED_BODY()
	TStaticArray<FQuickSlot, 3>	Slots;
	int32						SelectedIndex;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTAG_API UQuickSlotComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuickSlotComponent(const FObjectInitializer& ObjectInitializer);

	void Next();
	void Previous();
	
	// executes a quickslot action instance
	void UseSelected();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void AssignSlot(int32 Index, TSubclassOf<UObject> ActionClass);

private:
	FQuickSlotBar QuickSlotBar;
};
