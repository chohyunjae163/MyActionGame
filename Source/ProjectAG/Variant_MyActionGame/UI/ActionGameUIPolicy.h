// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameUIPolicy.h"
#include "Types/MVVMViewModelContext.h"
#include "ActionGameUIPolicy.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogActionGameUI, Log, All);

USTRUCT()
struct FActionGameUILayerContent
{
	GENERATED_BODY()

	// The layout widget to spawn
	UPROPERTY(EditAnywhere, Category=UI)
	TSoftClassPtr<class UCommonActivatableWidget> ContentWidgetClass;

	// The layer to insert the widget in
	UPROPERTY(EditAnywhere, Category=UI, meta=(Categories="UI.Layer"))
	FGameplayTag LayerID;
};

/**
 * Blueprint UI Policy should inherit this class
 * add viewmodel instances 
 * push game ui layers when the layout is added to the viewport
 */
UCLASS(MinimalAPI)
class UActionGameUIPolicy : public UGameUIPolicy
{
	GENERATED_BODY()

public:
	void GetCharacterViewModelContext(OUT FMVVMViewModelContext& ViewModelContext) const;
	
protected:
	// ~ begin UGameUIPolicy 
	virtual void OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout) override;
	// ~ end UGameUIPolicy
	
private:
	void AddViewModelInstancesToGlobalCollection(const UGameInstance* GameInstance);
	void PushContentToLayers(const ULocalPlayer* Player);
	
private:
	UPROPERTY(EditDefaultsOnly, Category=UI, meta=(TitleProperty="{ContentWidgetClass} + {LayerID}"))
	TArray<FActionGameUILayerContent> UI_LayerContents;

	//character view model context
	UPROPERTY(EditDefaultsOnly, Category=ViewModel)
	FMVVMViewModelContext CharacterViewModelContext;

};
