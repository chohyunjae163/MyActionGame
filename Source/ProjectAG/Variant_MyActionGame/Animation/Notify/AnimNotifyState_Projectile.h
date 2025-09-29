// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Interface/CacheBoneTransformInterface.h"


#include "AnimNotifyState_Projectile.generated.h"

/**
 *  notify state for notifying projectile spawn
 */
UCLASS(Abstract)
class PROJECTAG_API UAnimNotifyState_Projectile : public UAnimNotifyState, public ICacheBoneTransformInterface
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
#if WITH_EDITOR
	//~ Begin ICacheBoneTransform Interface
	virtual FName GetBoneName() override { return BoneName; }
	virtual void Cache(const TConstArrayView<FTransform>& InBoneCSTransforms) override {};
	virtual void ClearCache() override {};
	//~ End ICacheBoneTransform Interface
#endif
	
protected:
	// number of projectiles 
	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	int Num;

	// gap between projectiles
	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	float Gap;

	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	FName BoneName = TEXT("pelvis");

	UPROPERTY(VisibleAnywhere,Category=ActionGameProjectile, meta=(MakeEditWidget))
	TArray<FTransform> CachedProjectileLocalTransforms;
};

UCLASS()
class PROJECTAG_API UAnimNotifyState_ProjectileCircle : public UAnimNotifyState_Projectile
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

#if WITH_EDITOR
	virtual void DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;
protected:
	virtual void Cache(const TConstArrayView<FTransform>& InBoneCSTransforms) override;
#endif


protected:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	float Radius;

	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	float Height;

	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile)
	float Pitch;

	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile, meta = (UIMin=0.0f,ClampMin=0.0f))
	float MinAngle = 0.0f;

	UPROPERTY(EditInstanceOnly,Category=ActionGameProjectile, meta = (UIMax=180.0f,ClampMax=180.0f))
	float MaxAngle = 180.0f;
	
#endif


};

