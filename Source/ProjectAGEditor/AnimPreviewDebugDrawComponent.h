// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "AnimPreviewDebugDrawComponent.generated.h"


/*
 * 애니매이션 프리뷰 에디터에서 디버그용 Shape을 그리기 위한 컴포넌트
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTAGEDITOR_API UAnimPreviewDebugDrawComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UAnimPreviewDebugDrawComponent();
	// Sets default values for this component's properties
	void Init(const FCollisionShape& InCollisionShape,TConstArrayView<FTransform> InTransform)
	{
		CollisionShape = InCollisionShape;
		Transforms = InTransform;
	}

	// 필수 오버라이드
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public:
	FCollisionShape		CollisionShape;
	TArray<FTransform>	Transforms;
};
