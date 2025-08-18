// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ActionGameAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UActionGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
protected:
	//for a walk blendspace. negative is left
	UPROPERTY(BlueprintReadOnly=Right)
	float Move_R;

	//for a walk blendspace. negative is backward
	UPROPERTY(BlueprintReadOnly,DisplayName=Forward)
	float Move_F;
};
