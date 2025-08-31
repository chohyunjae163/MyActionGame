#pragma once



#include "Interface/AssignableActionInterface.h"

#include "AssignableActionBase.generated.h"



UCLASS(Abstract)
class UAssignableActionBase : public UObject, public IAssignableActionInterface
{
	GENERATED_BODY()

	virtual void Execute(APawn* Instigator, class UAbilitySystemComponent* ASC) override {}
};