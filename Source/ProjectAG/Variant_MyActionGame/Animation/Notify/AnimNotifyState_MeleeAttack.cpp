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
	
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	const FGameplayTag Channel = ActionGameGameplayTags::TAG_Animation_MeleeAttack_Message;
	const FMeleeAttackMessage Message {
		.Owner = MeshComp->GetOwner(),
		.CollisionShape = Shape.ToCollisionShape(),
		.BoneCSTransforms = BoneCSTransforms,
	};
	GameplayMessageSubsystem.BroadcastMessage<FMeleeAttackMessage>(Channel,Message);
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

	//todo: notify melee attack end
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	const FGameplayTag Channel = ActionGameGameplayTags::TAG_Animation_MeleeAttack_Message;
	
	GameplayMessageSubsystem.BroadcastMessage<FMeleeAttackMessage>(Channel,FMeleeAttackMessage());

	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UAnimNotifyState_MeleeAttack::GetShapes(FCollisionShape& OutShape, TArray<FTransform>& OutTransforms)
{
	OutTransforms.Empty();
	for (FTransform Transform : BoneCSTransforms)
	{
		OutTransforms.Add(Transform);
	}

	OutShape = Shape.ToCollisionShape();
}

void UAnimNotifyState_MeleeAttack::SetBoneCSTransforms(const TConstArrayView<FTransform>& InBoneCSTransforms)
{
	BoneCSTransforms = InBoneCSTransforms;
}
