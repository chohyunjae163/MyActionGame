#pragma once



#include "IDetailCustomization.h"


DECLARE_MULTICAST_DELEGATE_OneParam(
	FOnAnimNotifyPicked,
	UObject*           /*ClickedObject*/);

class FAnimNotifyCustomDetails : public IDetailCustomization
{
public:
	static TSharedRef<class IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FAnimNotifyCustomDetails);
	}

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;


	static FOnAnimNotifyPicked OnAnimNotifySelected;
};
