// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Interact_Pickup.h"

#include "Variant_MyActionGame/ActorComponent/InteractableObjectComponent.h"
#include "Variant_MyActionGame/ActorComponent/InteractableObserverComponent.h"
#include "Variant_MyActionGame/ActorComponent/InventoryComponent.h"


void UGA_Interact_Pickup::OnMontageFinished()
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	UInventoryComponent* InventoryComponent = Avatar->FindComponentByClass<UInventoryComponent>();
	check(IsValid(InventoryComponent));
	const UInteractableObserverComponent* ObserverComponent = Avatar->FindComponentByClass<UInteractableObserverComponent>();
	check(IsValid(ObserverComponent));
	UInteractableObjectComponent* InteractableObjectComponent = ObserverComponent->GetInteractable().Get();
	UItemDefinition* ItemDef = InteractableObjectComponent->GetItemDefinition();
	InventoryComponent->AddItem(ItemDef);
}
