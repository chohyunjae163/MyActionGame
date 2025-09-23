// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_Projectile.h"

#pragma region UAnimNotifyState_Projectile

void UAnimNotifyState_Projectile::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	
}

void UAnimNotifyState_Projectile::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}



#pragma endregion

#pragma region UAnimNotifyState_ProjectileCircle


#if WITH_EDITOR

void UAnimNotifyState_ProjectileCircle::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UAnimNotifyState_ProjectileCircle::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UAnimNotifyState_ProjectileCircle::DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp,
                                                     const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const
{
	Super::DrawInEditor(PDI, MeshComp, Animation, NotifyEvent);

	if (Radius <= 0.0f)
	{
		return;
	}

	const FVector& Base = MeshComp->GetComponentLocation() + FVector(0.f,0.f,Height);
	const FVector& Axis = FVector(1.0f, 0.0f, 0.0f);
	const FVector& X_Align = MeshComp->GetForwardVector().RotateAngleAxis(Pitch,Axis);
	const FVector& Y_Align = MeshComp->GetUpVector().RotateAngleAxis(Pitch,Axis);
	constexpr int32 Sections = 32;
	constexpr uint8 DepthPriority = 0;
	const FLinearColor Red = FLinearColor::Red;
	DrawArc(PDI,Base,X_Align,Y_Align,MinAngle,MaxAngle,Radius,Sections,Red,DepthPriority);
}
#endif


#pragma endregion