#pragma once
#include "NativeGameplayTags.h"


namespace ActionGameGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Animation_MeleeAttack_Message);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LookMouse);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MeleeAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interact);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Initialized_AbilitySystem);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(WorldInteraction_CanInteract);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(WorldInteraction_PickupItem);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CharacterEvent);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CharacterEvent_UseConsumable);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UIEvent_QuickSlotChanged);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PlayerEvent_InventoryUpdated);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SaveEvent_Request);
}
