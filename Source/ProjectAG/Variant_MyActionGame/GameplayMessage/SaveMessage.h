#pragma once


#include "SaveMessage.generated.h"

USTRUCT(BlueprintType)
struct FRequestSaveMessage
{
	GENERATED_BODY()
	
	TWeakObjectPtr<UActorComponent>		Requester;
};