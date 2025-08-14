

#include "MathUtilLib.h"	

namespace MathUtil
{
	TArray<FTransform> InterpolateBetween(const FTransform& A, const FTransform& B)
	{
		const FQuat QA = A.GetRotation().GetNormalized();
		const FQuat QB = B.GetRotation().GetNormalized();
		const float thetaRad = QA.AngularDistance(QB);
		const float thetaDegree = FMath::RadiansToDegrees(thetaRad);
		int32 NumBetween = thetaDegree / 5.0f;
		TArray<FTransform> Out;
		if (NumBetween > 0)
		{
			Out.Reserve(NumBetween);
			for (int i = 0; i < NumBetween; i++)
			{
				const float a = i / static_cast<float>(NumBetween);
				FTransform T;
				T.Blend(A,B,a);
				Out.Emplace(T);
			}
		}
		return Out;
	}
}
