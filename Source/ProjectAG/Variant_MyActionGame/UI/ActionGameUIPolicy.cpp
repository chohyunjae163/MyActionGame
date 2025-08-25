// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameUIPolicy.h"
#include "CommonActivatableWidget.h"
#include "CommonLocalPlayer.h"
#include "CommonUIExtensions.h"
#include "MVVMGameSubsystem.h"
#include "ViewModel/CharacterViewModel.h"

DEFINE_LOG_CATEGORY(LogActionGameUI);

void UActionGameUIPolicy::GetCharacterViewModelContext(FMVVMViewModelContext& ViewModelContext) const
{
	ViewModelContext = CharacterViewModelContext;
}

void UActionGameUIPolicy::OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout)
{
	Super::OnRootLayoutAddedToViewport(LocalPlayer, Layout);

	AddViewModelInstancesToGlobalCollection(LocalPlayer->GetGameInstance());
	PushContentToLayers(LocalPlayer);

}

void UActionGameUIPolicy::AddViewModelInstancesToGlobalCollection(const UGameInstance* GameInstance)
{
	if(IsValid(GameInstance) == false)
	{
		UE_LOG(LogActionGameUI,Warning,TEXT(""));
		return;
	}
	
	const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	check(IsValid(MVVMSubsystem));

	UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
	if (IsValid(ViewModelCollection))
	{
		UCharacterViewModel* CharacterViewModel = NewObject<UCharacterViewModel>();
		ViewModelCollection->AddViewModelInstance(
			CharacterViewModelContext,
			CharacterViewModel
			);			
	}
}

void UActionGameUIPolicy::PushContentToLayers(const ULocalPlayer* Player)
{
	for (const FActionGameUILayerContent& LayerContent : UI_LayerContents)
	{
		TSubclassOf<UCommonActivatableWidget> ContentWidgetClass = LayerContent.ContentWidgetClass.LoadSynchronous();
		if (ensure(ContentWidgetClass))
		{
			const UCommonActivatableWidget* AddedWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(Player, LayerContent.LayerID, ContentWidgetClass);
			ensure(IsValid(AddedWidget));
		}			
	}
}
