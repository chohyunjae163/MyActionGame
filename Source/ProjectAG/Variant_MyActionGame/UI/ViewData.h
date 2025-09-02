#pragma once


#include "ViewData.generated.h"


USTRUCT(BlueprintType)
struct FItemViewData
{
	GENERATED_BODY()
	
	FPrimaryAssetId ItemAssetId;
	int32 Quantity;
};