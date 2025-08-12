// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Variant_MyActionGame/ActionGameShapeParam.h"
#include "AnimNotifyState_MeleeAttack.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTAG_API UAnimNotifyState_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()


public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

#if WITH_EDITOR
	void SetBoneCSTransforms(const TConstArrayView<FTransform>& InBoneCSTransforms);
#endif


private:
#if WITH_EDITOR
	void DebugDraw();
#endif
public:
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditInstanceOnly, Category=ActionGame,DisplayName=Bone)
	FBoneReference BoneRef;
	UPROPERTY(EditInstanceOnly, Category=ActionGame)
	FActionGameShapeParam ShapeParam;
#endif

private:
	//베이크한 트랜스폼 데이터
	TArray<const FTransform> BoneCSTransforms; 
};
