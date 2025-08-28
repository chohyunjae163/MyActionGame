// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Interact.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}

	UAbilityTask_PlayMontageAndWait* Task =
	UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		MontageToPlay
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

void UGA_Interact::OnMontageFinished()
{
}

void UGA_Interact::OnMontageInterrupted()
{
}

void UGA_Interact::OnMontageCancelled()
{
}
