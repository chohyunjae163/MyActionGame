#pragma once



#include "IDetailCustomization.h"


DECLARE_MULTICAST_DELEGATE_OneParam(
	FOnAnimNotifyPicked,
	const FAnimNotifyEvent&
	);

class FAnimNotifyCustomDetails final : public IDetailCustomization
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
