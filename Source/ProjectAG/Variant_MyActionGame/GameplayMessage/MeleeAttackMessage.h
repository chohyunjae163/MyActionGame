#pragma once


#include "MeleeAttackMessage.generated.h"

USTRUCT(BlueprintType)
struct FMeleeAttackMessage
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor>		Owner;
	FCollisionShape				CollisionShape;
	TConstArrayView<FTransform>	BoneCSTransforms;
};