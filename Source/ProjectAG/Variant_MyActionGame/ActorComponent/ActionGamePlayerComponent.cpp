// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_MyActionGame/ActorComponent/ActionGamePlayerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/Input/ActionGameInputComponent.h"


const FName UActionGamePlayerComponent::NAME_ActorFeatureName("ActionGamePlayer");

UActionGamePlayerComponent::UActionGamePlayerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputConfig(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UActionGamePlayerComponent::OnRegister()
{
	Super::OnRegister();

	// Register with the init state system early, this will only work if this is a game world
	RegisterInitStateFeature();
}

// Called when the game starts
void UActionGamePlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TryToChangeInitState(ActionGameGameplayTags::InitState_Spawned);
	CheckDefaultInitialization();
}


void UActionGamePlayerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool UActionGamePlayerComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState,
                                                    FGameplayTag DesiredState) const
{
	return true;
}

void UActionGamePlayerComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager,
	FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == ActionGameGameplayTags::InitState_DataAvailable &&
		DesiredState == ActionGameGameplayTags::InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		UInputComponent* InputComponent = Pawn->InputComponent;
		InitializePlayerInput(InputComponent);
	}
}

void UActionGamePlayerComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	const APlayerController* PlayerController = GetController<APlayerController>();
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem*	Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	//todo: register input mapping context
	for (const UInputMappingContext* MappingContext : DefaultInputMappings)
	{
		Subsystem->AddMappingContext(MappingContext,0);
	}

	//todo: bind input move
	UActionGameInputComponent* ActionGameInputComponent = Cast<UActionGameInputComponent>(PlayerInputComponent);
	ActionGameInputComponent->BindNativeAction(
		InputConfig,
		ActionGameGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::Input_Move);
}



void UActionGamePlayerComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	
}

void UActionGamePlayerComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = {
		ActionGameGameplayTags::InitState_Spawned,
		ActionGameGameplayTags::InitState_DataAvailable,
		ActionGameGameplayTags::InitState_DataInitialized,
		ActionGameGameplayTags::InitState_GameplayReady,
	};
	ContinueInitStateChain(StateChain);
}

void UActionGamePlayerComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (IsValid(Controller))
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator Rotator{0.f,Controller->GetControlRotation().Yaw,0.0f};

		if (Value.X != 0.0f)
		{
			const FVector MovementDir = Rotator.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDir,Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDir = Rotator.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDir,Value.Y);
		}
	}
}

void UActionGamePlayerComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	
}

