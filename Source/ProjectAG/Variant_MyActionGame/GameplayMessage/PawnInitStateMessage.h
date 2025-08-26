#pragma once


#include "PawnInitStateMessage.generated.h"

USTRUCT(BlueprintType)
struct FPawnGameReadyMessage
{
	GENERATED_BODY()

	TWeakObjectPtr<APawn>							Pawn;
	TWeakObjectPtr<class UAbilitySystemComponent>	PawnASC;
};