// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackTraceComponent.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/MeleeAttackMessage.h"

// Sets default values for this component's properties
UMeleeAttackTraceComponent::UMeleeAttackTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	// ...
}


// Called when the game starts
void UMeleeAttackTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = MessageSystem.RegisterListener(ActionGameGameplayTags::TAG_Animation_MeleeAttack_Message,this,&ThisClass::OnAnimMeleeAttackMessage);
	
}

void UMeleeAttackTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.UnregisterListener(ListenerHandle);
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UMeleeAttackTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	constexpr float SecondPerFrame = 1 / 30.f;
	const uint8 NumCheck = DeltaTime / SecondPerFrame;
	for (int32 i = 0; i < NumCheck; i++)
	{
		if (FTransform StartTransform,EndTransform; Transforms.Dequeue(StartTransform))
		{
			if (Transforms.Peek(EndTransform))
			{
				FVector Start = StartTransform.GetLocation();
				FVector End = EndTransform.GetLocation();
				UWorld* World = GetWorld();
				TArray<FHitResult> Hits;
				FQuat Quat = StartTransform.GetRotation();
				FCollisionObjectQueryParams Params;
				Params.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
				Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(GetOwner());
				CollisionParams.bDebugQuery = true;
				if (World->SweepMultiByObjectType(Hits,Start,End,Quat,Params,CollisionShape))
				{
					//todo:
					//try attack
				}				
			}
	
		}
		
	}

}

void UMeleeAttackTraceComponent::OnAnimMeleeAttackMessage(FGameplayTag Channel,
	const struct FMeleeAttackMessage& Message)
{
	SetComponentTickEnabled(false);
	if (Message.Owner != GetOwner())
	{
		return;
	}

	if (Message.BoneCSTransforms.Num() < 2)
	{
		return;
	}
	
	//hjcho:
	//트레이스할 트랜스폼이 있을때만 component tick on
	SetComponentTickEnabled(true);
	CollisionShape = Message.CollisionShape;
	AttackElapsedTime = 0.0f;
	Transforms.Empty();
	for (FTransform Transform : Message.BoneCSTransforms)
	{
		Transforms.Enqueue(Transform);
	}

}


