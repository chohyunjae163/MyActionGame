#pragma once


#include "CharacterEventMessage.generated.h"

USTRUCT(BlueprintType)
struct FCharacterConsumableMessage
{
	GENERATED_BODY()

	int32 SlotIndex;
};