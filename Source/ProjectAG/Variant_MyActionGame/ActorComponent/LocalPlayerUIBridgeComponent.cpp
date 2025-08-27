// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalPlayerUIBridgeComponent.h"

#include "AbilitySystemComponent.h"
#include "GameUIManagerSubsystem.h"
#include "MVVMGameSubsystem.h"
#include "Variant_MyActionGame/ActionGameGameplayTags.h"
#include "Variant_MyActionGame/GameplayMessage/PawnInitStateMessage.h"
#include "Variant_MyActionGame/Player/ActionGamePlayerState.h"
#include "Variant_MyActionGame/UI/ActionGameUIPolicy.h"
#include "Variant_MyActionGame/UI/ViewModel/PlayerViewModel.h"


// Sets default values for this component's properties
ULocalPlayerUIBridgeComponent::ULocalPlayerUIBridgeComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULocalPlayerUIBridgeComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = GameplayMessageSubsystem.RegisterListener(
		ActionGameGameplayTags::InitState_GameplayReady,
		this,
		&ThisClass::OnPawnGameReady);
}

void ULocalPlayerUIBridgeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameplayMessageSubsystem& GameplayMessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	GameplayMessageSubsystem.UnregisterListener(ListenerHandle);

	// @fixme: this cannot be done here 
	/*
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	AActionGamePlayerState* PS = PC->GetPlayerState<AActionGamePlayerState>();
	check(IsValid(PS));
	UAbilitySystemComponent* MyASC = PS->GetAbilitySystemComponent();
	UPlayerViewModel* PlayerViewModel = GetPlayerViewModel();
	if (IsValid(PlayerViewModel))
	{
		PlayerViewModel->Deinitialize(MyASC);
	}
	*/
	
	Super::EndPlay(EndPlayReason);
}

void ULocalPlayerUIBridgeComponent::OnPawnGameReady(struct FGameplayTag Channel,
	const struct FPawnGameReadyMessage& Message)
{
	APlayerController* LocalPC = Cast<APlayerController>(GetOwner());
	if (Message.Sender == LocalPC->GetPawn())
	{
		AActionGamePlayerState* PS = LocalPC->GetPlayerState<AActionGamePlayerState>();
		check(IsValid(PS));
		UAbilitySystemComponent* MyASC = PS->GetAbilitySystemComponent();
		UPlayerViewModel* PlayerViewModel = GetPlayerViewModel();
		if (IsValid(PlayerViewModel))
		{
			UAbilitySystemComponent* InitializedASC = Cast<UAbilitySystemComponent>(Message.PawnASC.Get());
			if (MyASC == InitializedASC)
			{
				PlayerViewModel->Initialize(MyASC);
			}
		}
	}
}

UPlayerViewModel* ULocalPlayerUIBridgeComponent::GetPlayerViewModel() const
{
		
	UGameInstance* GameInstance =  GetWorld()->GetGameInstance();
	check(IsValid(GameInstance));
	
	if (UGameUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UActionGameUIPolicy* Policy = Cast<UActionGameUIPolicy>(UIManager->GetCurrentUIPolicy()))
		{
			const UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
			check(IsValid(MVVMSubsystem));
			UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection();
			if (IsValid(ViewModelCollection))
			{
				FMVVMViewModelContext Context = Policy->GetGlobalViewModelContext(UPlayerViewModel::StaticClass());
				UPlayerViewModel* PlayerViewModel = Cast<UPlayerViewModel>(ViewModelCollection->FindViewModelInstance(Context));
				return PlayerViewModel;
			}
		}
	}

	return nullptr;
}
