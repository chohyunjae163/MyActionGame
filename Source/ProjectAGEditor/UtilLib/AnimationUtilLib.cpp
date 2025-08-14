

#include "AnimationUtilLib.h"

#include "Engine/SkeletalMeshSocket.h"

namespace AnimationUtil
{
	FTransform GetCSTransform(UAnimSequenceBase* AnimSequence, FName BoneName, float InCurTime)
	{
		FMemMark Mark(FMemStack::Get());
		FCompactPose OutPose;
		TArray<FBoneIndexType> RequiredBoneIndexArray;
		USkeleton* Skeleton = AnimSequence->GetSkeleton();
		const FReferenceSkeleton& RefSkeleton = Skeleton->GetReferenceSkeleton();
		RequiredBoneIndexArray.AddUninitialized(RefSkeleton.GetNum());
		for (int32 BoneIndex = 0; BoneIndex < RequiredBoneIndexArray.Num(); ++BoneIndex)
		{
			RequiredBoneIndexArray[BoneIndex] = BoneIndex;
		}

		FBoneContainer BoneContainer(
			RequiredBoneIndexArray,
			UE::Anim::FCurveFilterSettings(UE::Anim::ECurveFilterMode::None),
			*AnimSequence->GetSkeleton());
		OutPose.ResetToRefPose(BoneContainer);
		FBlendedCurve OutCurve;
		OutCurve.InitFrom(BoneContainer);
		UE::Anim::FStackAttributeContainer TempAttributes;

		FAnimationPoseData AnimationPoseData(OutPose, OutCurve, TempAttributes);
		FAnimExtractContext ExtractionContext(InCurTime, false);

		AnimSequence->GetAnimationPose(AnimationPoseData, ExtractionContext);
		const FCompactPose& CurrentPose =  AnimationPoseData.GetPose();
		const FBoneContainer& CurrentBoneContainer = CurrentPose.GetBoneContainer();
		int32 BoneIndex = CurrentBoneContainer.GetPoseBoneIndexForBoneName(BoneName);
		FTransform LocalSocketTransform = FTransform::Identity;
		if (BoneIndex == INDEX_NONE)
		{
			int32 DummyIndex;
			USkeletalMeshSocket* SkeletonSocket = Skeleton->FindSocketAndIndex(BoneName, DummyIndex);
			BoneIndex = Skeleton->GetReferenceSkeleton().FindBoneIndex(SkeletonSocket->BoneName);
			LocalSocketTransform = SkeletonSocket->GetSocketLocalTransform();
		}
		const FCompactPoseBoneIndex CPIndex = CurrentPose.GetBoneContainer().MakeCompactPoseIndex(FMeshPoseBoneIndex(BoneIndex));
		FCSPose<FCompactPose> ComponentSpacePose;
		ComponentSpacePose.InitPose(CurrentPose);
		return LocalSocketTransform * ComponentSpacePose.GetComponentSpaceTransform(CPIndex);
	}
}
