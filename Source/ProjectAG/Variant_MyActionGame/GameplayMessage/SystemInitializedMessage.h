#pragma once


#include "SystemInitializedMessage.generated.h"

USTRUCT(BlueprintType)
struct FSystemInitializedMessage
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor>				SystemOwner;
	TWeakObjectPtr<UActorComponent>		SystemComponent;
};