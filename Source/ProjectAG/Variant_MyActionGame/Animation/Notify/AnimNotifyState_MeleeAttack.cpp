// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_MeleeAttack.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/MeleeAttackMessage.h"

void UAnimNotifyState_MeleeAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (IsValid(GetWorld()) == false)
	{
		return;
	}
	if (GetWorld()->IsEditorWorld())
	{
		return;
	}
	FCollisionShape CollisionShape;
	if(Shape.ToCollisionShape(OUT CollisionShape))
	{
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		const FGameplayTag Channel = ActionGameGameplayTags::TAG_Animation_MeleeAttack_Message;

		const FMeleeAttackMessage Message {
			.Owner = MeshComp->GetOwner(),
			.CollisionShape = CollisionShape,
			.BoneCSTransforms = BoneCSTransforms,
		};
		GameplayMessageSubsystem.BroadcastMessage<FMeleeAttackMessage>(Channel,Message);		
	}

}

void UAnimNotifyState_MeleeAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	
	if (IsValid(GetWorld()) == false)
	{
		return;
	}
	if (GetWorld()->IsEditorWorld())
	{
		return;
	}

	// notify melee attack end
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	const FGameplayTag Channel = ActionGameGameplayTags::TAG_Animation_MeleeAttack_Message;


	//send an empty message
	GameplayMessageSubsystem.BroadcastMessage<FMeleeAttackMessage>(Channel,FMeleeAttackMessage());

	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

bool UAnimNotifyState_MeleeAttack::GetShapes(FCollisionShape& OutShape, TArray<FTransform>& OutTransforms,FLinearColor& InDrawColor)
{
	if (BoneCSTransforms.IsEmpty())
	{
		return false;
	}
	OutTransforms.Empty();
	for (FTransform Transform : BoneCSTransforms)
	{
		OutTransforms.Add(Transform);
	}

	InDrawColor = DrawColor;

	 if (Shape.ToCollisionShape(OutShape))
	 {
		 return true;
	 }
	
	return false;
}

#if WITH_EDITOR

FName UAnimNotifyState_MeleeAttack::GetBoneName()
{
	return SocketName;
}

void UAnimNotifyState_MeleeAttack::Cache(const TConstArrayView<FTransform>& InBoneCSTransforms)
{
	BoneCSTransforms = InBoneCSTransforms;
}

void UAnimNotifyState_MeleeAttack::ClearCache()
{
	BoneCSTransforms.Empty();
}

void UAnimNotifyState_MeleeAttack::DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp,
                                                const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const
{
	Super::DrawInEditor(PDI, MeshComp, Animation, NotifyEvent);

	if (SocketName.IsNone())
	{
		return;
	}

	FCollisionShape CollisionShape;
	if (Shape.ToCollisionShape(OUT CollisionShape))
	{
		switch ( CollisionShape.ShapeType )
		{
		case ECollisionShape::Line:
			break;
		case ECollisionShape::Box:
			break;
		case ECollisionShape::Sphere:
			break;
		case ECollisionShape::Capsule:
			const FTransform& BoneTransform = MeshComp->GetSocketTransform(SocketName);
			const float Radius = CollisionShape.GetCapsuleRadius();
			const float HalfHeight = CollisionShape.GetCapsuleHalfHeight();
			const FVector UnitXAxis = BoneTransform.GetUnitAxis( EAxis::X );
			const FVector UnitYAxis = BoneTransform.GetUnitAxis( EAxis::Y );
			const FVector UnitZAxis = BoneTransform.GetUnitAxis( EAxis::Z );
			const FVector CapsuleAdjust = BoneTransform.GetRotation().GetUpVector() * HalfHeight;
			const FVector BaseLocation = BoneTransform.GetLocation() + CapsuleAdjust;
			DrawWireCapsule(
				PDI,
				BaseLocation,
				UnitXAxis,
				UnitYAxis,
				UnitZAxis,
				DrawColor,
				Radius,
				HalfHeight,
				NumSides,
				SDPG_World,
				Thickness
			);	
			break;
		}	
	}
}

#endif
