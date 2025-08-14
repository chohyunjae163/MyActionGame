// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Variant_MyActionGame/ActionGameShapeParam.h"
#include "Variant_MyActionGame/Interface/BakeBoneTransformInterface.h"
#include "Variant_MyActionGame/Interface/DrawShapesInterface.h"
#include "AnimNotifyState_MeleeAttack.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTAG_API UAnimNotifyState_MeleeAttack
	: public UAnimNotifyState
	, public IDrawShapesInterface
	, public IBakeBoneTransformInterface
{
	GENERATED_BODY()


public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	//~ Begin IDrawShapes Interface 
	virtual bool GetShapes(FCollisionShape& OutShape, TArray<FTransform>& OutTransforms) override;
	//~ End IDrawShapes Interface 

#if WITH_EDITOR
	//~ Begin IBakeBoneTransform Interface
	virtual FName GetBoneName() override;
	virtual void SetBoneCSTransforms(const TConstArrayView<FTransform>& InBoneCSTransforms) override;
	//~ End IBakeBoneTransform Interface
	
	virtual void DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;

#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditInstanceOnly, Category=ActionGame,DisplayName=Bone)
	FName SocketName;
	UPROPERTY(EditInstanceOnly, Category=ActionGame)
	FActionGameShape Shape;

	UPROPERTY(EditInstanceOnly, Category=ActionGame)
	FLinearColor DrawColor = FLinearColor::White;

	UPROPERTY(EditInstanceOnly, Category=ActionGame)
	int NumSides = 24;

	UPROPERTY(EditInstanceOnly, Category=ActionGame)
	float Thickness = 0.2f;
#endif

private:
	//this data is filled in editor-time, used in runtime.
	UPROPERTY()
	TArray<FTransform> BoneCSTransforms; 
};
