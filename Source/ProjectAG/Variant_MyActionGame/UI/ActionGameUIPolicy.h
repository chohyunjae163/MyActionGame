// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameHUD.h"
#include "GameplayTagContainer.h"
#include "GameUIPolicy.h"
#include "ActionGameUIPolicy.generated.h"


USTRUCT()
struct FActionGameUILayer
{
	GENERATED_BODY()

	// The layout widget to spawn
	UPROPERTY(EditAnywhere, Category=UI)
	TSoftClassPtr<UActionGameHUD> LayerClass;

	// The layer to insert the widget in
	UPROPERTY(EditAnywhere, Category=UI, meta=(Categories="UI.Layer"))
	FGameplayTag LayerID;
};


/**
 * Blueprint UI Policy should inherit this class
 */
UCLASS(MinimalAPI)
class UActionGameUIPolicy : public UGameUIPolicy
{
	GENERATED_BODY()

public:
	TConstArrayView<FActionGameUILayer> GetLayers() const
	{
		return UI_Layers;
	}

protected:
	//
	virtual void OnRootLayoutAddedToViewport(UCommonLocalPlayer* LocalPlayer, UPrimaryGameLayout* Layout) override;

private:
	void PushContentToLayers(const ULocalPlayer* Player);
private:
	UPROPERTY(EditDefaultsOnly, Category=UI, meta=(TitleProperty="{LayerClass} + {LayerID}"))
	TArray<FActionGameUILayer> UI_Layers; 
};
