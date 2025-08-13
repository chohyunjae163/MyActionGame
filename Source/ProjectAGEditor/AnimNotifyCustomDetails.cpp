
#include "AnimNotifyCustomDetails.h"

#include "DetailLayoutBuilder.h"


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
	OnAnimNotifySelected.Broadcast(ClickedObj);

}
