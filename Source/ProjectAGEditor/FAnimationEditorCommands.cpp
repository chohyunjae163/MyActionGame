#include "FAnimationEditorCommands.h"


#define LOCTEXT_NAMESPACE "AnimationEditorCommands"

void FAnimationEditorCommands::RegisterCommands()
{
	
	UI_COMMAND(
		BakeMeleeAttack,
		"Bake Melee Attack",
		"Bake Melee Attack on current Animation asset",
		EUserInterfaceActionType::Button,
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