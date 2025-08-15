#pragma once


#include "AnimNotifyCustomDetails.h"
#include "AnimPreviewDebugDrawComponent.h"
#include "FAnimationEditorCommands.h"
#include "IAnimationEditorModule.h"
#include "IPersonaPreviewScene.h"
#include "IPersonaToolkit.h"
#include "Animation/DebugSkelMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Modules/ModuleManager.h"
#include "UtilLib/AnimationUtilLib.h"
#include "UtilLib/EditorUtilLib.h"
#include "UtilLib/MathUtilLib.h"
#include "Variant_MyActionGame/Interface/CacheBoneTransformInterface.h"
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
				FAnimationEditorCommands::Get().ClearBakes,
				FExecuteAction::CreateRaw(this,&FProjectAGEditorModule::OnClearBakes));			
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
			FText::FromString("Bake Data on the selected AnimNotify"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Palette")
		);
		
		Builder.AddToolBarButton(
			FAnimationEditorCommands::Get().ClearBakes,
			NAME_None,
			FText::FromString("Clear Bake Data"),
			FText::FromString("Clear Bake Data on the selected AnimNotify"),
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
			if (ICacheBoneTransformInterface* BakeBoneTransformInterface = Cast<ICacheBoneTransformInterface>(NotifyState))
			{
				const float TriggerTime = NotifyEvent.GetTriggerTime();
				const float EndTime = NotifyEvent.GetEndTriggerTime();
				TArray<FTransform> BoneCSTransforms;
				const FName BoneName = BakeBoneTransformInterface->GetBoneName();
				EditorUtil::Bake(AnimSequence,TriggerTime,EndTime,BoneName, OUT BoneCSTransforms);
				BakeBoneTransformInterface->Cache(BoneCSTransforms);
				UpdateDraw(NotifyEvent.NotifyStateClass,BoneCSTransforms);
			}
		}
		AnimAsset->Modify();
	}
	
	void UpdateDraw(UAnimNotifyState* NotifyState,TConstArrayView<FTransform> BoneCSTransforms) const
	{
		//draw baked transforms with shapes and color
		if (IDrawShapesInterface* DrawShapes = Cast<IDrawShapesInterface>(NotifyState))
		{
			FCollisionShape Shape;
			TArray<FTransform> Transforms;
			FLinearColor DrawColor;
			if (DrawShapes->GetShapes(OUT Shape,OUT Transforms,OUT DrawColor))
			{
				if (IsValid(PreviewDrawComponent))
				{
					PreviewDrawComponent->Update(Shape,BoneCSTransforms,DrawColor);
				}				
			}				
		}
	}
	

	void OnClearBakes()
	{
		if (IsValid(SelectedAnimNotify) == false)
		{
			return;
		}
		UAnimNotifyState* NotifyState = Cast<UAnimNotifyState>(SelectedAnimNotify);
		if (ICacheBoneTransformInterface* BakeBoneTransformInterface = Cast<ICacheBoneTransformInterface>(NotifyState))
		{
			BakeBoneTransformInterface->ClearCache();
			if (IsValid(PreviewDrawComponent))
			{
				PreviewDrawComponent->Clear();
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
			FLinearColor DrawColor;
			if (DrawShapes->GetShapes(OUT Shape,OUT Transforms,OUT DrawColor))
			{ 
				if (IsValid(PreviewDrawComponent))
				{
					PreviewDrawComponent->Update(Shape,Transforms,DrawColor);
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
