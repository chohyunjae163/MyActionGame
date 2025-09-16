// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_MeleeAttack.h"

#include "AbilitySystemLog.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "FuncLib/ActionGameBPFuncLib.h"

void UGA_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}
	
	const TArray<TSoftObjectPtr<UAnimMontage>>& AttackMotionSet = UActionGameBPFuncLib::GetAttackMotionSet(Cast<APawn>(ActorInfo->AvatarActor));
	if (AttackMotionSet.IsEmpty())
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}
	UAnimMontage* DefaultAttackMontage = AttackMotionSet[0].Get();
	UAnimMontage* CurrentAnimMontage = ActorInfo->GetAnimInstance()->GetCurrentActiveMontage();
	if (IsValid(CurrentAnimMontage) && DefaultAttackMontage == CurrentAnimMontage)
	{
		//if playing the same montage, there might be a combo section
	}

	UAnimMontage* MontageToPlay = DefaultAttackMontage;
	FName StartSection = NAME_None;
	UAbilityTask_PlayMontageAndWait* Task =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			MontageToPlay,
			1.0f,
			StartSection
		);

	if (!IsValid(Task))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	Task->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageFinished);
	Task->OnCompleted.AddDynamic(this, &ThisClass::OnMontageFinished);
	Task->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageInterrupted);
	Task->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);

	Task->ReadyForActivation();
}

void UGA_MeleeAttack::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}


void UGA_MeleeAttack::OnMontageInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_MeleeAttack::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
