// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDefinition.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "InventoryComponent.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);


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
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnWorldInteractItem(struct FGameplayTag Channel, const struct FInstancedStruct& Message );
	bool TryAddItem(const FPrimaryAssetId& ItemAssetId);
	FItemInstance* FindItem(const FInventoryItemHandle& Handle);
	void UseItem(const FInventoryItemHandle& Handle);
	void RemoveItem(FInventoryItemHandle Handle);

	const UItemDefinition* ResolveDef(const FPrimaryAssetId& Id);
	void OnLoadAssetComplete();
	

private:
	TArray<FItemInstance>	Items;
	TQueue<FPrimaryAssetId> PendingAssetsToAdd;
	FGameplayMessageListenerHandle ListenerHandle;
};
