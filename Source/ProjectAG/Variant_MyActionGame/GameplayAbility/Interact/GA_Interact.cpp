// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Interact.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "ActorComponent/InteractableObjectComponent.h"
#include "ActorComponent/InteractableObserverComponent.h"

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}

	AActor* MyAvatar = ActorInfo->AvatarActor.Get();
	if (!IsValid(MyAvatar))
	{
		return;
	}

	UInteractableObserverComponent* InteractableObserverComponent = MyAvatar->FindComponentByClass<UInteractableObserverComponent>();
	if (IsValid(InteractableObserverComponent) == false)
	{
		return;
	}

	UInteractableObjectComponent* InteractableObjectComponent = InteractableObserverComponent->GetCurrentInteractable().Get();
	if (IsValid(InteractableObjectComponent))
	{
		const FInteractionSpec& InteractionSpec = InteractableObjectComponent->GetInteractionSpec();
		const FName InteractionTag = InteractionSpec.Tag.GetTagName(); //for later querying
		
		// play a montage
		if (IsValid(InteractionSpec.InstigatorMontage))
		{
			
			UAbilityTask_PlayMontageAndWait* Task =
				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this,
					InteractionTag,
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

		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());

		FGameplayTag Channel = InteractionSpec.Tag;
		FInstancedStruct Payload = InteractionSpec.Payload;
		GameplayMessageSubsystem.BroadcastMessage(Channel,Payload);
	}

}

void UGA_Interact::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_Interact::OnMontageInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}


void UGA_Interact::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
