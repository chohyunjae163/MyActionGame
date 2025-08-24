// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameHUD.h"

#include "AbilitySystemComponent.h"
#include "MVVMGameSubsystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/SystemInitializedMessage.h"
#include "Variant_MyActionGame/Player/ActionGamePlayerState.h"
#include "ViewModel/CharacterViewModel.h"

void AActionGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	check(IsValid(PlayerOwner));

	UGameInstance* GameInstance =  GetGameInstance();
	check(IsValid(GameInstance));
	
	const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	check(IsValid(MVVMSubsystem));

	UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	if (IsValid(ViewModelCollection))
	{
		FName ViewModelName = TEXT("PlayerCharacterViewModel");
		
		Context.ContextClass = UCharacterViewModel::StaticClass();
		Context.ContextName = ViewModelName;
		UCharacterViewModel* CharacterViewModel = NewObject<UCharacterViewModel>();
		ViewModelCollection->AddViewModelInstance(
			Context,
			CharacterViewModel
			);
	}

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::Initialized_AbilitySystem,
		this,
		&ThisClass::OnSystemInitialized);
	
}

void AActionGameHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(ListenerHandle);

	UCharacterViewModel* CharacterViewModel = GetCharacterViewModel();
	if (IsValid(CharacterViewModel))
	{
		AActionGamePlayerState* PS = GetOwningPlayerController()->GetPlayerState<AActionGamePlayerState>();
		CharacterViewModel->Deinitialize(PS->GetAbilitySystemComponent());
	}
	
	Super::EndPlay(EndPlayReason);
}

class UCharacterViewModel* AActionGameHUD::GetCharacterViewModel() const
{
	UGameInstance* GameInstance =  GetGameInstance();
	check(IsValid(GameInstance));
	
	const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	check(IsValid(MVVMSubsystem));

	UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	if (IsValid(ViewModelCollection))
	{
		return Cast<UCharacterViewModel>(ViewModelCollection->FindViewModelInstance(Context));
	}
	return nullptr;
}

void AActionGameHUD::OnSystemInitialized(struct FGameplayTag Channel, const struct FSystemInitializedMessage& Message)
{
	UCharacterViewModel* CharacterViewModel = GetCharacterViewModel();
	if (IsValid(CharacterViewModel))
	{
		AActionGamePlayerState* PS = GetOwningPlayerController()->GetPlayerState<AActionGamePlayerState>();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (ASC == Message.SystemComponent)
		{
			CharacterViewModel->Initialize(ASC);
		}
	}
}
