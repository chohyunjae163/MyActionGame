#pragma once


#include "PawnInitStateMessage.generated.h"

USTRUCT(BlueprintType)
struct FPawnGameReadyMessage
{
	GENERATED_BODY()

	TWeakObjectPtr<APawn>							Sender;
	TWeakObjectPtr<class UAbilitySystemComponent>	PawnASC;
};