// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ActionGameCharacter.generated.h"


/**
 *  A base character class used across the Action Game.
 *  It is a lightweight shell Actor that can represent any character
 *  in a game.(PC,NPC,Monster) It is intentionally kept 
 *  minimal and relies on external data definitions (PawnData).
 */
UCLASS(MinimalAPI,Blueprintable)
class AActionGameCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionGameCharacter();

protected:

	
	// ~ begin APawn interface
	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* NewController) override;
	// ~ end APawn interface

	// ~ begin ACharacter interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// ~ end ACharacter interface
	
protected:
	// any action game character needs this.
	UPROPERTY(VisibleAnywhere,Category="Action Game")
	TObjectPtr<class UActionGamePawnComponent> ActionGamePawnComponent;

	//enables interacting with the world interactables
	UPROPERTY(VisibleAnywhere,Category="Action Game")
	TObjectPtr<class UInteractableObserverComponent> InteractableObserverComponent;
	
	
};
