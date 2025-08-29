
#include "ActionGameGameplayTags.h"


namespace ActionGameGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(TAG_Animation_MeleeAttack_Message, "Animation.MeleeAttack.Message");

	UE_DEFINE_GAMEPLAY_TAG(InitState_Spawned, "InitState.Spawned");
	UE_DEFINE_GAMEPLAY_TAG(InitState_DataAvailable, "InitState.DataAvailable");
	UE_DEFINE_GAMEPLAY_TAG(InitState_DataInitialized, "InitState.DataInitialized");
	UE_DEFINE_GAMEPLAY_TAG(InitState_GameplayReady, "InitState.GameplayReady");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LookMouse, "InputTag.LookMouse");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MeleeAttack, "InputTag.MeleeAttack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interact, "InputTag.Interact");
	
	UE_DEFINE_GAMEPLAY_TAG(Initialized_AbilitySystem, "Initialized.AbilitySystem");

	UE_DEFINE_GAMEPLAY_TAG(WorldInteraction_CanInteract, "WorldInteraction.CanInteract");
	UE_DEFINE_GAMEPLAY_TAG(WorldInteraction_PickupItem, "WorldInteraction.PickupItem");
}