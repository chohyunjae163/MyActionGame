// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "ActionGamePlayerComponent.generated.h"


/**
 * Component that sets up
 * 1. input
 * 2. camera handling
 * for player controlled pawns (or bots that simulate players).
 * This depends on a ActionGamePawnComponent to coordinate initialization.
 */
UCLASS(MinimalAPI, ClassGroup=(ActionGame), meta=(BlueprintSpawnableComponent) )
class UActionGamePlayerComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionGamePlayerComponent(const FObjectInitializer& ObjectInitializer);

	static const FName NAME_ActorFeatureName;
	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface

	//handle inputs
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
	void Input_Move(const struct FInputActionValue& InputActionValue);
	void Input_LookMouse(const struct FInputActionValue& InputActionValue);

	//camera related
	
protected:
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);


protected:
	UPROPERTY(EditAnywhere)
	TArray<class UInputMappingContext*> DefaultInputMappings;
	
	UPROPERTY(EditDefaultsOnly,Category=ActionGame,DisplayName="Input Config")
	TObjectPtr<class UActionGameInputConfig> InputConfig;
};
