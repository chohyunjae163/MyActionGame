#pragma once

namespace AnimationUtil
{
	FTransform GetCSTransform(UAnimSequenceBase* AnimSequence, FName BoneName, float InCurTime);
}
