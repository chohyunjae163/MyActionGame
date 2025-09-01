#pragma once



#include "Interface/AssignableActionInterface.h"

#include "AssignableActionBase.generated.h"



/*
 * a single action that can be assigned to objects and be executed
 */
UCLASS(Abstract)
class UAssignableActionBase : public UObject, public IAssignableActionInterface
{
	GENERATED_BODY()

	virtual void Execute(APawn* Instigator, class UAbilitySystemComponent* ASC) override {}
};