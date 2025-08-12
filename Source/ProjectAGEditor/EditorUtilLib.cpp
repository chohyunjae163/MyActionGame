#pragma once

#include "EditorUtilLib.h"
#include "IAnimationEditor.h"
#include "IHasPersonaToolkit.h"
#include "IPersonaToolkit.h"


namespace EditorUtil
{
	UAnimationAsset* GetActiveAnimationAsset()
	{
		if (GEditor)
		{
			if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			{
				TArray<IAssetEditorInstance*> OpenEditors =  AssetEditorSubsystem->GetAllOpenEditors();
				float LastActivationTime = -MAX_FLT;
				IAssetEditorInstance* ActiveEditor = nullptr;
				for (IAssetEditorInstance* OpenEditor : OpenEditors)
				{
					if (OpenEditor->GetLastActivationTime() > LastActivationTime)
					{
						ActiveEditor = OpenEditor;
						LastActivationTime = OpenEditor->GetLastActivationTime();
					}
				}
				if (ActiveEditor != nullptr)
				{
					if (const IAnimationEditor* AnimationEditor = static_cast<IAnimationEditor*>(ActiveEditor))
					{
						const IPersonaToolkit& PersonaToolkit = AnimationEditor->GetPersonaToolkit().Get();
						return PersonaToolkit.GetAnimationAsset();		
					}
				}
			}
		}
		
		return nullptr;
	}
}
