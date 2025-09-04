#pragma once


#include "PlayerEventMessage.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInventoryUpdated
{
	GENERATED_BODY()

	TArray<FItemInstance> ItemList;
};