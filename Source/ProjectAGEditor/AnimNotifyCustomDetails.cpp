
#include "AnimNotifyCustomDetails.h"
#include "DetailLayoutBuilder.h"
#include "Animation/EditorNotifyObject.h"

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
