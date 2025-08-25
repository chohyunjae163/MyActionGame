// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGamePlayerState.h"
#include "AbilitySystemComponent.h"
#include "GameUIManagerSubsystem.h"
#include "MVVMGameSubsystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"

#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/ActorComponent/MyAbilitySystemComponent.h"
#include "Variant_MyActionGame/GameplayAttribute/ActionGameCharacterAttributeSet.h"
#include "Variant_MyActionGame/GameplayMessage/SystemInitializedMessage.h"
#include "Variant_MyActionGame/UI/ActionGameUIPolicy.h"
#include "Variant_MyActionGame/UI/ViewModel/CharacterViewModel.h"


class UMVVMGameSubsystem;

AActionGamePlayerState::AActionGamePlayerState(const FObjectInitializer& ObjectInitializer)
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//...

	PlayerAttributeSet = CreateDefaultSubobject<UActionGameCharacterAttributeSet>(TEXT("PlayerAttributeSet"));
}

UAbilitySystemComponent* AActionGamePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AActionGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

		
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::Initialized_AbilitySystem,
		this,
		&ThisClass::OnSystemInitialized);
}

void AActionGamePlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(ListenerHandle);

	UCharacterViewModel* CharacterViewModel = GetCharacterViewModel();
	if (IsValid(CharacterViewModel))
	{
		CharacterViewModel->Deinitialize(AbilitySystemComponent);
	}
	
	Super::EndPlay(EndPlayReason);
}


void AActionGamePlayerState::OnSystemInitialized(struct FGameplayTag Channel,
                                                 const struct FSystemInitializedMessage& Message)
{
	UCharacterViewModel* CharacterViewModel = GetCharacterViewModel();
	if (IsValid(CharacterViewModel))
	{
		if (AbilitySystemComponent == Message.SystemComponent)
		{
			CharacterViewModel->Initialize(AbilitySystemComponent);
		}
	}
}


class UCharacterViewModel* AActionGamePlayerState::GetCharacterViewModel() const
{
	UGameInstance* GameInstance =  GetGameInstance();
	check(IsValid(GameInstance));
	
	const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	check(IsValid(MVVMSubsystem));

	UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	if (IsValid(ViewModelCollection))
	{
		if (UGameUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
		{
			if (UActionGameUIPolicy* Policy = Cast<UActionGameUIPolicy>(UIManager->GetCurrentUIPolicy()))
			{
				FMVVMViewModelContext Context;
				Policy->GetCharacterViewModelContext(Context);
				return Cast<UCharacterViewModel>(ViewModelCollection->FindViewModelInstance(Context));
			}
		}
		
	}
	return nullptr;
}