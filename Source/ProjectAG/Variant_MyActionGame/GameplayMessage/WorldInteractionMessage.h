#pragma once


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
	class UInteractableObserverComponent*	InteractionObserver;
	UPROPERTY()
	class UInteractableObjectComponent*		InteractionObject;
	EWorldInteractionStatus					InteractionStatus;
};