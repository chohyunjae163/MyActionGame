#pragma once
#include "IAnimationEditor.h"
#include "IPersonaToolkit.h"


namespace EditorUtil
{
    TSharedPtr<IPersonaToolkit> GetActivePersonaToolKit();
    IAnimationEditor* GetActiveAnimationEditor();
    UAnimationAsset* GetActiveAnimationAsset(); 
}
