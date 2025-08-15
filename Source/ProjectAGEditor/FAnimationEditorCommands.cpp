#include "FAnimationEditorCommands.h"


#define LOCTEXT_NAMESPACE "AnimationEditorCommands"

void FAnimationEditorCommands::RegisterCommands()
{
	
	UI_COMMAND(
		BakeMeleeAttack,
		"Bake Melee Attack",
		"Bake Melee Attack on current Anim Notify",
		EUserInterfaceActionType::Button,
		FInputChord()
		);

	UI_COMMAND(
		ClearBakes,
		"Clear Bake Data",
		"CLear Bake Data on current Anim Notify",
		EUserInterfaceActionType::ToggleButton,
		FInputChord()
	);
	
	UI_COMMAND(
		ToggleViewDebugDraw,
		"Toggle View Debug Draw",
		"Toggle View Debug Draw on current Animation asset",
		EUserInterfaceActionType::ToggleButton,
		FInputChord()
	);
}



#undef LOCTEXT_NAMESPACE