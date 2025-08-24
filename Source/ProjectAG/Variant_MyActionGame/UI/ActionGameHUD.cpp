// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameHUD.h"

#include "MVVMGameSubsystem.h"
#include "MVVMSubsystem.h"
#include "ViewModel/CharacterViewModel.h"

void AActionGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	check(IsValid(PlayerOwner));

	UGameInstance* GameInstance =  PlayerOwner->GetGameInstance();
	check(IsValid(GameInstance));
	
	const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	check(IsValid(MVVMSubsystem));

	UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	if (IsValid(ViewModelCollection))
	{
		FMVVMViewModelContext Context;
		FName ViewModelName = TEXT("PlayerCharacterViewModel");
		Context.ContextClass = UCharacterViewModel::StaticClass();
		Context.ContextName = ViewModelName;
		UCharacterViewModel* CharacterViewModel = NewObject<UCharacterViewModel>();
		ViewModelCollection->AddViewModelInstance(
			Context,
			CharacterViewModel
			);
	}
}
