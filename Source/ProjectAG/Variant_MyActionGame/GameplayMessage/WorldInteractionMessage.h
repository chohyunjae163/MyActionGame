#pragma once
#include "StructUtils/InstancedStruct.h"


#include "WorldInteractionMessage.generated.h"

UENUM(BlueprintType)
enum class EWorldInteractionStatus : uint8
{
	Invalid = 0,
	Ready = 1,
	Interacting = 2,
	Complete = 3,
};

USTRUCT(BlueprintType)
struct FWorldInteractionMessage
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<class UInteractableObserverComponent>	InteractionObserver = nullptr;
	UPROPERTY()
	TObjectPtr<class UInteractableObjectComponent>		InteractionObject = nullptr;
	
	EWorldInteractionStatus								InteractionStatus = EWorldInteractionStatus::Invalid;
};

USTRUCT(Category="World Interaction")
struct FWorldInteractionItemUnit
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="/Script/ProjectAG.ItemDefinition"))
	FPrimaryAssetId AssetId;

	UPROPERTY(EditAnywhere)
	int32 Quantity = 0;
};

USTRUCT(Category="World Interaction",DisplayName="Payload_WorldInteractionItemList")
struct FWorldItemInteractionPayload
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWorldInteractionItemUnit> Items;
};