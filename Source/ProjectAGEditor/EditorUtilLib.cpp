#pragma once

#include "EditorUtilLib.h"
#include "IAnimationEditor.h"
#include "IHasPersonaToolkit.h"
#include "IPersonaToolkit.h"


namespace EditorUtil
{
	
	IAnimationEditor* GetActiveAnimationEditor()
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
				return static_cast<IAnimationEditor*>(ActiveEditor);
			}
		}
		
		return nullptr;
	}

	TSharedPtr<IPersonaToolkit> GetActivePersonaToolKit()
	{
		if (const IAnimationEditor* AnimationEditor = GetActiveAnimationEditor())
		{
			TSharedPtr<IPersonaToolkit> PersonaToolkit = AnimationEditor->GetPersonaToolkit();
			return PersonaToolkit;		
		}
		
		return nullptr;
	}
	
	UAnimationAsset* GetActiveAnimationAsset()
	{
		TSharedPtr<IPersonaToolkit> PersonaToolkit = GetActivePersonaToolKit();
		return PersonaToolkit->GetAnimationAsset();
	}

}
