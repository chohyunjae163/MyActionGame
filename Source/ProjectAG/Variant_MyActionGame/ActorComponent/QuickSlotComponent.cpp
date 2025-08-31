// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotComponent.h"

#include "AssignableAction/AssignableAction_Consumable.h"
#include "Player/ActionGamePlayerState.h"


// Sets default values for this component's properties
UQuickSlotComponent::UQuickSlotComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



// Called when the game starts
void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//sample test
	AssignSlot(0,UAssignableAction_Consumable::StaticClass());
	
}

void UQuickSlotComponent::AssignSlot(const int32 Index, TSubclassOf<UObject> ActionClass)
{
	QuickSlotBar.Slots[Index].ActionClass = ActionClass;
	UObject* ActionInstance = NewObject<UObject>(this,ActionClass);
	QuickSlotBar.Slots[Index].ActionInstance = ActionInstance;
}


void UQuickSlotComponent::UseSelected()
{
	const int32 SelectedIndex = QuickSlotBar.SelectedIndex;
	IAssignableActionInterface* ActionInstance = Cast<IAssignableActionInterface>(QuickSlotBar.Slots[SelectedIndex].ActionInstance);
	if (ActionInstance != nullptr)
	{
		const AActionGamePlayerState* MyPlayerState = GetPlayerState<AActionGamePlayerState>();
		UAbilitySystemComponent* MyASC = MyPlayerState->GetAbilitySystemComponent();
		ActionInstance->Execute(GetPawn<APawn>(),MyASC);		
	}

}
