// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Projectile.generated.h"

/**
 *  notify state for notifying projectile spawn
 */
UCLASS(Abstract,MinimalAPI)
class UAnimNotifyState_Projectile : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	// number of projectiles 
	UPROPERTY(EditInstanceOnly)
	int Num;

	// gap between projectiles
	UPROPERTY(EditInstanceOnly)
	float Gap;
};

UCLASS(MinimalAPI)
class UAnimNotifyState_ProjectileCircle : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

#if WITH_EDITOR
	virtual void DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;
#endif

protected:
	
	UPROPERTY(EditInstanceOnly)
	float Radius;

	UPROPERTY(EditInstanceOnly)
	float Height;

	UPROPERTY(EditInstanceOnly)
	float Pitch;

	UPROPERTY(EditInstanceOnly, meta = (UIMin=0.0f,ClampMin=0.0f))
	float MinAngle = 0.0f;

	UPROPERTY(EditInstanceOnly, meta = (UIMax=180.0f,ClampMax=180.0f))
	float MaxAngle = 180.0f;
};

