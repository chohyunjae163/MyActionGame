#pragma once


#include "AnimPreviewDebugDrawComponent.h"
#include "EditorUtilLib.h"
#include "FAnimationEditorCommands.h"
#include "IAnimationEditorModule.h"
#include "IPersonaPreviewScene.h"
#include "IPersonaToolkit.h"
#include "Selection.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Modules/ModuleManager.h"
#include "Variant_MyActionGame/Animation/Notify/AnimNotifyState_MeleeAttack.h"


class FProjectAGEditorModule : public FDefaultGameModuleImpl
{
	
	virtual void ShutdownModule() override
	{
		if (GEditor)
		{
			UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
			if (AssetEditorSubsystem)
			{
				AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
			}
		}
	}




	virtual void StartupModule() override
	{
		FEditorDelegates::OnEditorInitialized.AddRaw(this, &FProjectAGEditorModule::OnPostEditorInit);
		FAnimationEditorCommands::Register();
		//Bake Melee Attack Data
		{
			//register command
		
			AnimationEditorCommands = MakeShared<FUICommandList>();
			AnimationEditorCommands->MapAction(
				FAnimationEditorCommands::Get().BakeMeleeAttack,
				FExecuteAction::CreateRaw(this,&FProjectAGEditorModule::OnBakeAttackCommandClicked));
			AnimationEditorCommands->MapAction(
				FAnimationEditorCommands::Get().ToggleViewDebugDraw,
				FExecuteAction::CreateRaw(this,&FProjectAGEditorModule::OnToggleViewDebugDraw));
		}

		
		// 툴바 익스텐더 생성
		ToolbarExtender = MakeShared<FExtender>();
		ToolbarExtender->AddToolBarExtension(
			"Asset",                   // 기존 섹션 뒤에 붙이기(필요 시 "Settings" 등으로 변경)
			EExtensionHook::After,
			AnimationEditorCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FProjectAGEditorModule::AddToolbarButton));

		IAnimationEditorModule& AnimEditorModule =
			FModuleManager::LoadModuleChecked<IAnimationEditorModule>("AnimationEditor");
		AnimEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

	};

	void AddToolbarButton(FToolBarBuilder& Builder)
	{
		Builder.AddToolBarButton(
			FAnimationEditorCommands::Get().BakeMeleeAttack,
			NAME_None,
			FText::FromString("Bake Melee Attack"),
			FText::FromString("Bake Melee Attack for the current Animation asset"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Palette")
		);

		Builder.AddToolBarButton(
			FAnimationEditorCommands::Get().ToggleViewDebugDraw,
			NAME_None,
			FText::FromString("Toggle Debug Draw"),
			FText::FromString("Toggle Debug Draw for the current Animation asset"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Palette")
		);		
	}
	
	void OnBakeAttackCommandClicked()
	{
		// 현재 활성 애니메이션 에디터의 선택 에셋 얻기
		UAnimationAsset* AnimAsset = EditorUtil::GetActiveAnimationAsset();
		UAnimSequenceBase* AnimSequence = Cast<UAnimSequence>(AnimAsset);
		for (const FAnimNotifyEvent& NotifyEvent : AnimSequence->Notifies)
		{
			UAnimNotifyState* NotifyState = NotifyEvent.NotifyStateClass;
			if (UAnimNotifyState_MeleeAttack* AnimNotifyState_MeleeAttack = Cast<UAnimNotifyState_MeleeAttack>(NotifyState); IsValid(AnimNotifyState_MeleeAttack))
			{
				const float TriggerTime = NotifyEvent.GetTriggerTime();
				const float EndTime = NotifyEvent.GetEndTriggerTime();
				constexpr float SecondPerFrame = 1 / 30.f;
				TArray<FTransform> BoneCSTransforms;
				for (float CurTime  = TriggerTime; CurTime <= EndTime; CurTime += SecondPerFrame)
				{
					FMemMark Mark(FMemStack::Get());
					FCompactPose OutPose;
					TArray<FBoneIndexType> RequiredBoneIndexArray;
					RequiredBoneIndexArray.AddUninitialized(AnimSequence->GetSkeleton()->GetReferenceSkeleton().GetNum());
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
					FAnimExtractContext ExtractionContext(CurTime, false);

					AnimSequence->GetAnimationPose(AnimationPoseData, ExtractionContext);
					const FCompactPose& CurrentPose =  AnimationPoseData.GetPose();
					const FBoneContainer& CurrentBoneContainer = CurrentPose.GetBoneContainer();
					int32 BoneIndex = CurrentBoneContainer.GetPoseBoneIndexForBoneName(AnimNotifyState_MeleeAttack->BoneRef.BoneName);
					FCompactPoseBoneIndex CPIndex = CurrentPose.GetBoneContainer().MakeCompactPoseIndex(FMeshPoseBoneIndex(BoneIndex));
					FCSPose<FCompactPose> ComponentSpacePose;
					ComponentSpacePose.InitPose(CurrentPose);
					const FTransform& CS_Transform = ComponentSpacePose.GetComponentSpaceTransform(CPIndex);
					BoneCSTransforms.Emplace(CS_Transform);
				}

				AnimNotifyState_MeleeAttack->SetBoneCSTransforms(BoneCSTransforms);
			}
		}
	}

	void OnToggleViewDebugDraw()
	{
		UAnimationAsset* AnimAsset = EditorUtil::GetActiveAnimationAsset();
		UAnimSequenceBase* AnimSequence = Cast<UAnimSequence>(AnimAsset);
		for (const FAnimNotifyEvent& NotifyEvent : AnimSequence->Notifies)
		{
			UAnimNotifyState* NotifyState = NotifyEvent.NotifyStateClass;
		}
	}

	void OnPostEditorInit(double Duration)
	{
		if (GEditor)
		{
			UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
			if (AssetEditorSubsystem)
			{
				AssetEditorSubsystem->OnAssetEditorOpened().AddRaw(this, &FProjectAGEditorModule::OnAssetEditorOpened);
			}

			GEditor->GetSelectedObjects()->SelectionChangedEvent.AddRaw(this,&FProjectAGEditorModule::OnEditorObjectChanged);
		}
	}
	void OnAssetEditorOpened(UObject* Object)
	{
		if (Object->IsA<UAnimSequenceBase>())
		{
			TSharedPtr<IPersonaToolkit> PersonaToolkit = EditorUtil::GetActivePersonaToolKit();
			if (PersonaToolkit.IsValid())
			{
				const IPersonaToolkit& PersonaToolkitRef = PersonaToolkit.ToSharedRef().Get();
				IPersonaPreviewScene& PreviewScene = PersonaToolkitRef.GetPreviewScene().Get();
				UDebugSkelMeshComponent* PreviewComp = PreviewScene.GetPreviewMeshComponent();

				PreviewDrawComponent =
					NewObject<UAnimPreviewDebugDrawComponent>(PreviewComp);

				if (IsValid(PreviewDrawComponent))
				{
					//PreviewDrawComponent->Init();
					UWorld* PreviewWorld = PreviewScene.GetWorld();
					check(PreviewWorld);
					PreviewDrawComponent->RegisterComponentWithWorld(PreviewWorld);
					PreviewDrawComponent->AttachToComponent(PreviewComp, FAttachmentTransformRules::KeepWorldTransform);
				}
			}

		}
	}
	void OnEditorObjectChanged(UObject* Object)
	{
		if (Object->IsA<UAnimNotifyState>())
		{
			
		}
		else if (Object->IsA<UAnimNotifyState>())
		{
			
		}
	}

private:
	TSharedPtr<FUICommandList> AnimationEditorCommands;
	TSharedPtr<FExtender>      ToolbarExtender;


	TObjectPtr<UAnimPreviewDebugDrawComponent> PreviewDrawComponent;
};

IMPLEMENT_MODULE(FProjectAGEditorModule, ProjectAGEditor);
