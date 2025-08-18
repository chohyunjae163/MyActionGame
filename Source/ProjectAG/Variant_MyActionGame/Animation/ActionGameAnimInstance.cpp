// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_MyActionGame/Animation/ActionGameAnimInstance.h"

void UActionGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UActionGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
}

void UActionGameAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();
	if (IsValid(OwningActor))
	{
		const FRotator& ActorRotation = OwningActor->GetActorRotation();
		const FVector& Velocity = OwningActor->GetVelocity();
		const FVector& Local_V = ActorRotation.UnrotateVector(Velocity).GetSafeNormal();
		Move_F = Local_V.X;
		Move_R = Local_V.Y;
	}
}
