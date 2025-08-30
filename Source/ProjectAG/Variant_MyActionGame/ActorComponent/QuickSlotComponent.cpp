// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotComponent.h"


// Sets default values for this component's properties
UQuickSlotComponent::UQuickSlotComponent()
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
	IAssignableAction* ActionInstance = Cast<IAssignableAction>(QuickSlotBar.Slots[SelectedIndex].ActionInstance);
	ActionInstance->Execute(GetOwner());
}
