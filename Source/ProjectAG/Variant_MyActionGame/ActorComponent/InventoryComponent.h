// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDefinition.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interface/SaveParticipantInterface.h"
#include "InventoryComponent.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);


UCLASS(MinimalAPI,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UInventoryComponent : public UActorComponent, public ISaveParticipantInterface
{
	GENERATED_BODY()

	

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	
	//in case, one wants look at items.
	TConstArrayView<FItemInstance> GetItems() const { return ItemList; };

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnWorldInteractItem(struct FGameplayTag Channel, const struct FInstancedStruct& Message );
	void AddItem(const FPrimaryAssetId& Id,const UItemDefinition* ItemDef,int32 NewQuantity);
	FItemInstance* FindItem(const FInventoryItemHandle& Handle);
	void UseItem(const FInventoryItemHandle& Handle);
	void RemoveItem(FInventoryItemHandle Handle);

	static const UItemDefinition* TryResolveDef(const FPrimaryAssetId& Id);
	void OnLoadAssetComplete();

	// ~ begin ISaveParticipant Interface
	virtual void WriteToSave(class USaveGame* SaveGameObject) override;
	virtual void ReadFromSave(class USaveGame* SaveGameObject) override;
	// ~ end ISaveParticipant Interface
private:
	TArray<FItemInstance>	ItemList;
	TQueue<FPrimaryAssetId> PendingAssetsToAdd;
	FGameplayMessageListenerHandle ListenerHandle;
};
