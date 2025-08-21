// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameUIPolicy.h"

#include "CommonLocalPlayer.h"
#include "CommonUIExtensions.h"

void UActionGameUIPolicy::OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout)
{
	Super::OnRootLayoutAddedToViewport(LocalPlayer, Layout);

	PushContentToLayers(LocalPlayer);

}

void UActionGameUIPolicy::PushContentToLayers(const ULocalPlayer* Player)
{
	for (const FActionGameUILayer& GameUILayer : UI_Layers)
	{
		if (TSubclassOf<UCommonActivatableWidget> WidgetClass = GameUILayer.LayerClass.LoadSynchronous())
		{
			const UCommonActivatableWidget* AddedWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(Player, GameUILayer.LayerID, WidgetClass);
			ensure(IsValid(AddedWidget));
		}			
	}
}
