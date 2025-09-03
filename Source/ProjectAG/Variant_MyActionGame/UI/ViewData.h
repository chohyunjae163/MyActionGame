#pragma once


#include "ViewData.generated.h"


USTRUCT(BlueprintType)
struct FItemViewData
{
	GENERATED_BODY()

	FPrimaryAssetId AssetId;
	TSoftObjectPtr<class UPaperSprite> Icon;
	int32 Quantity;
};