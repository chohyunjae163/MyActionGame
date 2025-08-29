// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameCharacter.h"

#include "Variant_MyActionGame/ActorComponent/ActionGamePawnComponent.h"
#include "Variant_MyActionGame/ActorComponent/InteractableObserverComponent.h"

// Sets default values
AActionGameCharacter::AActionGameCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ActionGamePawnComponent = CreateDefaultSubobject<UActionGamePawnComponent>("ActionGamePawnComponent");
}

void AActionGameCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	UActionGamePawnComponent* PawnComponent = UActionGamePawnComponent::GetActionGamePawnComponent(this);
	PawnComponent->HandleControllerChanged();
}

void AActionGameCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	UActionGamePawnComponent* PawnComponent = UActionGamePawnComponent::GetActionGamePawnComponent(this);
	PawnComponent->HandlePlayerStateReplicated();
}

void AActionGameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UActionGamePawnComponent* PawnComponent = UActionGamePawnComponent::GetActionGamePawnComponent(this);
	PawnComponent->HandleControllerChanged();
}

void AActionGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UActionGamePawnComponent* PawnComponent = UActionGamePawnComponent::GetActionGamePawnComponent(this);
	PawnComponent->SetupPlayerInputComponent();
}

