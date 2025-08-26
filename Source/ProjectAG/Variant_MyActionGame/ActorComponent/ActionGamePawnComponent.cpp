// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePawnComponent.h"

#include "AbilitySystemComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/Data/ActionGamePawnData.h"
#include "Variant_MyActionGame/GameplayMessage/PawnInitStateMessage.h"
#include "Variant_MyActionGame/GameplayMessage/SystemInitializedMessage.h"
#include "Variant_MyActionGame/Player/ActionGamePlayerState.h"

const FName UActionGamePawnComponent::NAME_ActorFeatureName("ActionGamePawn");


// Sets default values for this component's properties
UActionGamePawnComponent::UActionGamePawnComponent(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UActionGamePawnComponent::OnRegister()
{
	Super::OnRegister();
	RegisterInitStateFeature();
}

// Called when the game starts
void UActionGamePawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// Listen for changes to all features
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);
	ensureMsgf(IsValid(PawnData),TEXT("Pawn Data must be set for the pawn"));
	TryToChangeInitState(ActionGameGameplayTags::InitState_Spawned);
	CheckDefaultInitialization();
}

void UActionGamePawnComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	UninitializeAbilitySystem();
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UActionGamePawnComponent::TickComponent(float DeltaTime, ELevelTick TickType,
											 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



bool UActionGamePawnComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState,
	FGameplayTag DesiredState) const
{
	APawn* Pawn = GetPawn<APawn>();
	if (!CurrentState.IsValid() && DesiredState == ActionGameGameplayTags::InitState_Spawned)
	{
		// As long as we are on a valid pawn, we count as spawned
		if (IsValid(Pawn))
		{
			return true;
		}
	}
	if (CurrentState == ActionGameGameplayTags::InitState_Spawned && DesiredState == ActionGameGameplayTags::InitState_DataAvailable)
	{
		const bool bHasAuthority = Pawn->HasAuthority();
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

		if (bHasAuthority || bIsLocallyControlled)
		{
			// Check for being possessed by a controller.
			if (!GetController<AController>())
			{
				return false;
			}

		}

		return true;
	}
	if (CurrentState == ActionGameGameplayTags::InitState_DataAvailable && DesiredState == ActionGameGameplayTags::InitState_DataInitialized)
	{
		// Transition to initialize if all features(components) have their data available
		const bool AllFeaturesReached_DataAvailable = Manager->HaveAllFeaturesReachedInitState(Pawn, ActionGameGameplayTags::InitState_DataAvailable,NAME_ActorFeatureName);
		return AllFeaturesReached_DataAvailable;
	}
	if (CurrentState == ActionGameGameplayTags::InitState_DataInitialized && DesiredState == ActionGameGameplayTags::InitState_GameplayReady)
	{
		//make sure other features(components) have their data initialized before moving on to GameplayReady
		ensure(Manager->HaveAllFeaturesReachedInitState(Pawn, ActionGameGameplayTags::InitState_DataInitialized,NAME_ActorFeatureName));
		return true;
	}

	return false;
}

void UActionGamePawnComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState,
	FGameplayTag DesiredState)
{
	if (CurrentState == ActionGameGameplayTags::InitState_DataInitialized && DesiredState == ActionGameGameplayTags::InitState_GameplayReady)
	{
		// ability system component must be ready at this stage.
		ensure(IsValid(AbilitySystemComponent));
		UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		const FGameplayTag Channel = ActionGameGameplayTags::InitState_GameplayReady;

		const FPawnGameReadyMessage Message {
			.Pawn = GetPawn<APawn>(),
			.PawnASC = AbilitySystemComponent,
		};
		GameplayMessageSubsystem.BroadcastMessage<FPawnGameReadyMessage>(Channel,Message);
	}
}

void UActionGamePawnComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	// If another feature is now in DataAvailable, see if we should transition to DataInitialized
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		if (Params.FeatureState == ActionGameGameplayTags::InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
	
}

void UActionGamePawnComponent::CheckDefaultInitialization()
{
	// Before checking our progress, try progressing any other features we might depend on
	CheckDefaultInitializationForImplementers();

	static const TArray<FGameplayTag> StateChain = {
		ActionGameGameplayTags::InitState_Spawned,
		ActionGameGameplayTags::InitState_DataAvailable,
		ActionGameGameplayTags::InitState_DataInitialized,
		ActionGameGameplayTags::InitState_GameplayReady
	};

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

void UActionGamePawnComponent::InitializeAbilitySystem(class UAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	check(InASC);
	check(InOwnerActor);

	if (AbilitySystemComponent == InASC)
	{
		// The ability system component hasn't changed.
		return;
	}

	if (IsValid(AbilitySystemComponent))
	{
		// Clean up the old ability system component.
		UninitializeAbilitySystem();
	}

	APawn* Pawn = GetPawnChecked<APawn>();
	AbilitySystemComponent = InASC;
	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, Pawn);
	
	UActionGameAbilitySet* AbilitySet = PawnData->AbilitySet;
	AbilitySet->GiveAbilities(AbilitySystemComponent);
	AbilitySet->ApplyEffects(AbilitySystemComponent);
}

void UActionGamePawnComponent::UninitializeAbilitySystem()
{
	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (IsValid(AbilitySystemComponent))
	{
		if (AbilitySystemComponent->GetAvatarActor() == GetOwner())
		{
			AbilitySystemComponent->CancelAbilities();
			AbilitySystemComponent->RemoveAllGameplayCues();

			if (AbilitySystemComponent->GetOwnerActor() != nullptr)
			{
				AbilitySystemComponent->SetAvatarActor(nullptr);
			}
			else
			{
				// If the ASC doesn't have a valid owner, we need to clear *all* actor info, not just the avatar pairing
				AbilitySystemComponent->ClearActorInfo();
			}
		}
	}
	AbilitySystemComponent = nullptr;
}

void UActionGamePawnComponent::HandleControllerChanged()
{
	CheckDefaultInitialization();
}

void UActionGamePawnComponent::HandlePlayerStateReplicated()
{
	CheckDefaultInitialization();
}

void UActionGamePawnComponent::SetupPlayerInputComponent()
{
	CheckDefaultInitialization();
}
