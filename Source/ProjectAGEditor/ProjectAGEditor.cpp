#pragma once


#include "AnimNotifyCustomDetails.h"
#include "AnimPreviewDebugDrawComponent.h"
#include "EditorUtilLib.h"
#include "FAnimationEditorCommands.h"
#include "IAnimationEditorModule.h"
#include "IPersonaPreviewScene.h"
#include "IPersonaToolkit.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Modules/ModuleManager.h"
#include "Variant_MyActionGame/Interface/BakeBoneTransformInterface.h"
#include "Variant_MyActionGame/Interface/DrawShapesInterface.h"


class FProjectAGEditorModule : public FDefaultGameModuleImpl
{
	
	virtual void ShutdownModule() override
	{
		if (GEditor)
		{
			if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();IsValid(AssetEditorSubsystem))
			{
				AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
			}
		}
	}

	

	virtual void StartupModule() override
	{
		FEditorDelegates::OnEditorInitialized.AddRaw(this, &FProjectAGEditorModule::OnPostEditorInit);
		FEditorDelegates::OnEditorPreExit.AddRaw(this,&FProjectAGEditorModule::OnPostEditorPreExit);
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

		
		// new toolbar extender 
		ToolbarExtender = MakeShared<FExtender>();
		ToolbarExtender->AddToolBarExtension(
			"Asset",                   
			EExtensionHook::After,
			AnimationEditorCommands,
			FToolBarExtensionDelegate::CreateRaw(this, &FProjectAGEditorModule::AddToolbarButton));

		//
		IAnimationEditorModule& AnimEditorModule =
			FModuleManager::LoadModuleChecked<IAnimationEditorModule>("AnimationEditor");
		AnimEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
		
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		FName ClassName = "EditorAnimBaseObj";
		PropertyModule.RegisterCustomClassLayout(
			ClassName,
			FOnGetDetailCustomizationInstance::CreateStatic(&FAnimNotifyCustomDetails::MakeInstance));
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
			if (NotifyEvent.NotifyStateClass != SelectedAnimNotify)
			{
				continue;
			}
			UAnimNotifyState* NotifyState = Cast<UAnimNotifyState>(SelectedAnimNotify);
			if (IBakeBoneTransformInterface* BakeBoneTransformInterface = Cast<IBakeBoneTransformInterface>(NotifyState))
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
					FAnimExtractContext ExtractionContext(CurTime, false);

					AnimSequence->GetAnimationPose(AnimationPoseData, ExtractionContext);
					const FCompactPose& CurrentPose =  AnimationPoseData.GetPose();
					const FBoneContainer& CurrentBoneContainer = CurrentPose.GetBoneContainer();
					const FName BoneName = BakeBoneTransformInterface->GetBoneName();
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
					const FTransform& CS_Transform = ComponentSpacePose.GetComponentSpaceTransform(CPIndex);
					BoneCSTransforms.Emplace(LocalSocketTransform * CS_Transform);		
				}

				BakeBoneTransformInterface->SetBoneCSTransforms(BoneCSTransforms);
				if (IDrawShapesInterface* DrawShapes = Cast<IDrawShapesInterface>(NotifyState))
				{
					FCollisionShape Shape;
					TArray<FTransform> Transforms;
					if (DrawShapes->GetShapes(OUT Shape,OUT Transforms))
					{
						if (IsValid(PreviewDrawComponent))
						{
							PreviewDrawComponent->Update(Shape,BoneCSTransforms);
						}				
					}				
				}


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
			if (IsValid(AssetEditorSubsystem))
			{
				AssetEditorSubsystem->OnAssetEditorOpened().AddRaw(this, &FProjectAGEditorModule::OnAssetEditorOpened);
				AssetEditorSubsystem->OnAssetClosedInEditor().AddRaw(this,&FProjectAGEditorModule::OnAssetEditorClosed);
			}
		}
	}

	void OnPostEditorPreExit()
	{
		if (GEditor)
		{
			UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
			if (IsValid(AssetEditorSubsystem))
			{
				AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
				AssetEditorSubsystem->OnAssetClosedInEditor().RemoveAll(this);
			}
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
					PreviewDrawComponent->AttachToComponent(PreviewComp, FAttachmentTransformRules::KeepWorldTransform);
				}

				FAnimNotifyCustomDetails::OnAnimNotifySelected.AddRaw(this,&FProjectAGEditorModule::OnAnimNotifySelected);
			}
		}
	}

	void OnAssetEditorClosed(UObject* Object, IAssetEditorInstance* AssetEditorInstance)
	{
		FAnimNotifyCustomDetails::OnAnimNotifySelected.RemoveAll(this);
	}
	
	void OnAnimNotifySelected(const FAnimNotifyEvent& NotifyEvent)
	{
		//todo: handle a animnotify too.
		UAnimNotifyState* NotifyState = NotifyEvent.NotifyStateClass;
		if (IDrawShapesInterface* DrawShapes = Cast<IDrawShapesInterface>(NotifyState))
		{
			FCollisionShape Shape;
			TArray<FTransform> Transforms;
			if (DrawShapes->GetShapes(OUT Shape,OUT Transforms))
			{ 
				if (IsValid(PreviewDrawComponent))
				{
					PreviewDrawComponent->Update(Shape,Transforms);
				}
			}
			SelectedAnimNotify = NotifyState;
			TSharedPtr<IPersonaToolkit> PersonaToolkit = EditorUtil::GetActivePersonaToolKit();
			if (PersonaToolkit.IsValid())
			{
				const IPersonaToolkit& PersonaToolkitRef = PersonaToolkit.ToSharedRef().Get();
				IPersonaPreviewScene& PreviewScene = PersonaToolkitRef.GetPreviewScene().Get();
				UWorld* PreviewWorld = PreviewScene.GetWorld();
				check(PreviewWorld);
				if (PreviewDrawComponent->IsRegistered())
				{
					PreviewDrawComponent->UnregisterComponent();
				}
				PreviewDrawComponent->RegisterComponentWithWorld(PreviewWorld);
			}

		}
	}



private:
	TSharedPtr<FUICommandList> AnimationEditorCommands;
	TSharedPtr<FExtender>      ToolbarExtender;

	TObjectPtr<UObject>			SelectedAnimNotify;
	TObjectPtr<UAnimPreviewDebugDrawComponent> PreviewDrawComponent;
};

IMPLEMENT_MODULE(FProjectAGEditorModule, ProjectAGEditor);
