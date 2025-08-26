#pragma once


#include "WorldInteractionMessage.generated.h"

UENUM(BlueprintType)
enum class EWorldInteractionStatus : uint8
{
	Available = 0,
	Interacting = 1,
	Complete = 2,
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