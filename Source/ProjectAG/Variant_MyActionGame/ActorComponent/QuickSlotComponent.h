// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuickSlotComponent.generated.h"

UINTERFACE()
class UAssignableAction : public UInterface { GENERATED_BODY() };

class IAssignableAction
{
	GENERATED_BODY()
public:
	// 실행
	virtual void Execute(AActor* Instigator) = 0;
};


//quickslot action


UCLASS(Abstract)
class UQuickSlotActionBase : public UObject, public IAssignableAction
{
	GENERATED_BODY()

	virtual void Execute(AActor* Instigator) override {}
};

UCLASS()
class UQuickSlotAction_ConsumeItem : public UQuickSlotActionBase
{
	GENERATED_BODY()

	
	virtual void Execute(AActor* Instigator) override {}
};

USTRUCT()
struct FQuickSlot
{
	GENERATED_BODY()
	
	TSubclassOf<IAssignableAction> ActionClass;

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
class PROJECTAG_API UQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuickSlotComponent();



	//
	void UseSelected();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void AssignSlot(int32 Index, TSubclassOf<UObject> ActionClass);

private:
	FQuickSlotBar QuickSlotBar;
};
