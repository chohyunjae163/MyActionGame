// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameButtonBase.h"

void UActionGameButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateButtonText(ButtonText);
}
