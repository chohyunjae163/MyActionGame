// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameUIPolicy.h"
#include "CommonActivatableWidget.h"
#include "CommonLocalPlayer.h"
#include "CommonUIExtensions.h"

void UActionGameUIPolicy::OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout)
{
	Super::OnRootLayoutAddedToViewport(LocalPlayer, Layout);

	PushContentToLayers(LocalPlayer);

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
