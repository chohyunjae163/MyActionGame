#pragma once



#include "IDetailCustomization.h"
#include "Variant_MyActionGame/Interface/CacheBoneTransformInterface.h"


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


class FMyAnimNotifyStateProjectileCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FMyAnimNotifyStateProjectileCustomization);
	}

	FReply OnMyButtonClicked() const;
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	ICacheBoneTransformInterface* CacheBoneTransformInterface;
};