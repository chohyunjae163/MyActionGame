#pragma once

#include "EditorUtilLib.h"

#include "AnimationUtilLib.h"
#include "IAnimationEditor.h"
#include "IHasPersonaToolkit.h"
#include "IPersonaToolkit.h"
#include "MathUtilLib.h"
#include "Engine/SkeletalMeshSocket.h"


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

	void Bake(UAnimSequenceBase* AnimSequence,
		float TriggerTime,
		float EndTime,
		FName BoneName,
		OUT TArray<FTransform>& OutBoneCSTransforms )
	{
		constexpr float SecondPerFrame = 1 / 30.f;
		FTransform PrevTransform = AnimationUtil::GetCSTransform(AnimSequence,BoneName,TriggerTime);
		for (float CurTime = TriggerTime + SecondPerFrame; CurTime <= EndTime; CurTime += SecondPerFrame)
		{
			const FTransform& CurTransform = AnimationUtil::GetCSTransform(AnimSequence,BoneName,CurTime);
			TArray<FTransform> BetweenTransforms = MathUtil::InterpolateBetween(PrevTransform,CurTransform);
			OutBoneCSTransforms.Emplace(PrevTransform);
			if (BetweenTransforms.Num() > 0)
			{
				OutBoneCSTransforms.Append(BetweenTransforms);
			}
			OutBoneCSTransforms.Emplace(CurTransform);
			PrevTransform = CurTransform;
		}
	}

}
