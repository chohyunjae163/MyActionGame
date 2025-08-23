// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ActionGameButtonBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI,Blueprintable)
class UActionGameButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	// UUserWidget interface
	virtual void NativePreConstruct() override;
	// End of UUserWidget interface

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonText(const FText& NewButtonText);
	
private:
	UPROPERTY(EditAnywhere, Category="Button")
	FText ButtonText;
};
