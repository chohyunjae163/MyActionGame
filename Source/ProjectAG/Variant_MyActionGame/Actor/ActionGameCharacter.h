// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ActionGameCharacter.generated.h"

UCLASS(MinimalAPI,Blueprintable)
class AActionGameCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 
	 * Called when this Pawn is possessed. Only called on the server (or in standalone).
	 * @param NewController The controller possessing this pawn
	 */
	virtual void PossessedBy(AController* NewController) override;
	/** Called when our Controller no longer possesses us. Only called on the server (or in standalone). */
	virtual void UnPossessed() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UActionGamePawnComponent> ActionGamePawnComponent;
	
	
};
