// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAG_API UPlayerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize();
	void Deinitialize() const;

	
};
