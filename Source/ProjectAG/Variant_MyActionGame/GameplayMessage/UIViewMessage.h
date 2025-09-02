#pragma once


#include "UIViewMessage.generated.h"

USTRUCT(BlueprintType)
struct FUI_QuickSlotChangedMessage
{
	GENERATED_BODY()

	int32 Index;
	FPrimaryAssetId ItemAssetId;
	int32 Quantity;
};