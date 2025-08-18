// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameCharacter.h"

#include "Variant_MyActionGame/ActorComponent/ActionGamePawnComponent.h"

// Sets default values
AActionGameCharacter::AActionGameCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ActionGamePawnComponent = CreateDefaultSubobject<UActionGamePawnComponent>("ActionGamePawnComponent");

}

// Called when the game starts or when spawned
void AActionGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActionGameCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AActionGameCharacter::UnPossessed()
{
	Super::UnPossessed();
}

// Called every frame
void AActionGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

