// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "InventoryComponent.generated.h"


USTRUCT()
struct FInventoryItemHandle
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid Guid; 

	bool IsValid() const { return Guid.IsValid(); }

	static FInventoryItemHandle NewHandle()
	{
		FInventoryItemHandle H;
		H.Guid = FGuid::NewGuid();
		return H;
	}

	bool operator==(const FInventoryItemHandle& Other) const
	{
		return Guid == Other.Guid;
	}
};


//runtime item info
USTRUCT()
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY()
	FInventoryItemHandle Handle;
	
	UPROPERTY(Transient)
	TObjectPtr<class UItemDefinition> Definition;

	UPROPERTY(Transient)
	int32 Quantity = 0;

	bool operator==(const FItemInstance& Other) const
	{
		return Handle == Other.Handle;
	}
};

UCLASS(MinimalAPI,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	
	//in case, one wants look at items.
	TConstArrayView<FItemInstance> GetItems() const { return Items; };

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
private:
	void OnInteractItem(struct FGameplayTag Channel, const struct FWorldInteractionItemMessage& Message );
	FInventoryItemHandle AddItem(class UItemDefinition* ItemDef);
	FItemInstance* FindItem(const FInventoryItemHandle& Handle);
	void UseItem(const FInventoryItemHandle& Handle);
	void RemoveItem(FInventoryItemHandle Handle);
	
private:
	TArray<FItemInstance> Items;

	FGameplayMessageListenerHandle ListenerHandle;
};
