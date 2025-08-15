#pragma once
#include "IAnimationEditor.h"
#include "IPersonaToolkit.h"


namespace EditorUtil
{
    TSharedPtr<IPersonaToolkit> GetActivePersonaToolKit();
    IAnimationEditor* GetActiveAnimationEditor();
    UAnimationAsset* GetActiveAnimationAsset();
    void Bake(UAnimSequenceBase* AnimSequence, float TriggerTime, float EndTime, FName BoneName, OUT TArray<FTransform>& OutBoneCSTransforms );
}
