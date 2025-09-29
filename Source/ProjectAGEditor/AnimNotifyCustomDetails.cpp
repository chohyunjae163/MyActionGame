
#include "AnimNotifyCustomDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Animation/EditorNotifyObject.h"


#define LOCTEXT_NAMESPACE "AnimNotifyCustomDetails"

FOnAnimNotifyPicked FAnimNotifyCustomDetails::OnAnimNotifySelected;

void FAnimNotifyCustomDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<>> Selected;
	DetailBuilder.GetObjectsBeingCustomized(Selected);
	if (Selected.Num() == 0)
	{
		return;
	}
	UObject* ClickedObj = Selected[0].Get();
	if (UEditorNotifyObject* EditorNotifyObject = Cast<UEditorNotifyObject>(ClickedObj); IsValid(EditorNotifyObject))
	{
		
		OnAnimNotifySelected.Broadcast(EditorNotifyObject->Event);
	}
}

void FMyAnimNotifyStateProjectileCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	// 선택된 객체 가져오기
	TArray<TWeakObjectPtr<UObject>> Objects = DetailBuilder.GetSelectedObjects();
	
	if (Objects.Num() > 0)
	{
		UEditorNotifyObject* EditorNotifyObject = Cast<UEditorNotifyObject>(Objects[0]);
		UAnimNotifyState* NotifyState = EditorNotifyObject->Event.NotifyStateClass;
		CacheBoneTransformInterface = Cast<ICacheBoneTransformInterface>(NotifyState);
	}
	
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("CustomButtons");
	
	Category.AddCustomRow(FText::FromString("Update Projectile Transforms"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(LOCTEXT("UpdateProjectileTransform", "Update Projectile Transforms"))
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SNew(SButton)
		.Text(FText::FromString("Update Transforms"))
		.OnClicked(FOnClicked::CreateSP(this, &FMyAnimNotifyStateProjectileCustomization::OnMyButtonClicked))
	];
}


FReply FMyAnimNotifyStateProjectileCustomization::OnMyButtonClicked() const
{
	TArray<FTransform> Transforms;
	CacheBoneTransformInterface->Cache(Transforms);

	return FReply::Handled();
}
