#pragma once
#include "Framework/Commands/Commands.h"

class FAnimationEditorCommands : public TCommands<FAnimationEditorCommands>
{
public:
	FAnimationEditorCommands()
	: TCommands<FAnimationEditorCommands>(
		TEXT("AnimationEditorTools"),
		NSLOCTEXT("AnimationEditorTools", "AnimationEditorTools", "Animation Editor Tools"),
		NAME_None,
		FAppStyle::GetAppStyleSetName()
	)
	{}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> BakeMeleeAttack;
	TSharedPtr<FUICommandInfo> ToggleViewDebugDraw;
};
