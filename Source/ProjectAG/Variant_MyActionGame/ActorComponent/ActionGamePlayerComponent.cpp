// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_MyActionGame/ActorComponent/ActionGamePlayerComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Components/GameFrameworkComponentManager.h"
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
	APawn* MyPawn = GetPawn<APawn>();
	if (CurrentState.IsValid() == false && DesiredState == ActionGameGameplayTags::InitState_Spawned)
	{
		return IsValid(MyPawn);
	}
	if (CurrentState == ActionGameGameplayTags::InitState_Spawned && DesiredState == ActionGameGameplayTags::InitState_DataAvailable)
	{
		check(IsValid(MyPawn));

		APlayerController* PC = GetController<APlayerController>();
		if (!IsValid(PC))
		{
			return false;
		}

		if (!IsValid(PC->GetLocalPlayer()))
		{
			return false;
		}
		
		return IsValid(MyPawn->InputComponent);
	}
	
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
		bPlayerInputInitialized = InitializePlayerInput(InputComponent);
	}
	if (CurrentState == ActionGameGameplayTags::InitState_DataInitialized)
	{
		ensureMsgf(bPlayerInputInitialized,TEXT("Player Input is not initialized!"));
	}
}

bool UActionGamePlayerComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	const APlayerController* PlayerController = GetController<APlayerController>();
	if (IsValid(PlayerController))
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		check(IsValid(LocalPlayer));
		UEnhancedInputLocalPlayerSubsystem*	Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		check(IsValid(Subsystem));

		for (const UInputMappingContext* MappingContext : DefaultInputMappings)
		{
			Subsystem->AddMappingContext(MappingContext,0);
		}

		UActionGameInputComponent* ActionGameInputComponent = Cast<UActionGameInputComponent>(PlayerInputComponent);
		if (IsValid(ActionGameInputComponent))
		{
			ActionGameInputComponent->BindAbilityActions(
				InputConfig,
				this,
				&ThisClass::Input_AbilityInputTagPressed,
				&ThisClass::Input_AbilityInputTagReleased);
			ActionGameInputComponent->BindNativeAction(
				InputConfig,
				ActionGameGameplayTags::InputTag_Move,
				ETriggerEvent::Triggered,
				this,
				&ThisClass::Input_Move);
			ActionGameInputComponent->BindNativeAction(
				InputConfig,
				ActionGameGameplayTags::InputTag_LookMouse,
				ETriggerEvent::Triggered,
				this,
				&ThisClass::Input_LookMouse);

			return true;
		}
	}
	return false;
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

void UActionGamePlayerComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	// handle ability input presssed
}

void UActionGamePlayerComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	// handle ability input released
}

void UActionGamePlayerComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	if (!IsValid(Pawn))
	{
		return;
	}
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
	APawn* Pawn = GetPawn<APawn>();

	if (!IsValid(Pawn))
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(-Value.Y);
	}
}

