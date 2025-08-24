// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameInGameHUD.h"

#include "CommonUIExtensions.h"
#include "NativeGameplayTags.h"
#include "Input/CommonUIInputTypes.h"


UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_ACTION_ESCAPE, "UI.Action.Escape");
UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");

void UActionGameInGameHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//ESC menu handling
	FBindUIActionArgs BindUIActionArgs(FUIActionTag::ConvertChecked(TAG_UI_ACTION_ESCAPE),FSimpleDelegate::CreateUObject(this,&ThisClass::HandleEscapeAction));
	FUIActionBindingHandle Handle = RegisterUIActionBinding(BindUIActionArgs);
}


void UActionGameInGameHUD::HandleEscapeAction()
{
	if (!EscapeMenuClass.IsNull())
	{
		UCommonUIExtensions::PushStreamedContentToLayer_ForPlayer(GetOwningLocalPlayer(), TAG_UI_LAYER_MENU, EscapeMenuClass);
	}
}


TOptional<FUIInputConfig> UActionGameInGameHUD::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
}