// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPreviewDebugDrawComponent.h"

class FAnimPreviewDrawShapeProxy : public FPrimitiveSceneProxy
{
public:
	FAnimPreviewDrawShapeProxy(const UPrimitiveComponent* InComponent,
		FCollisionShape& InCollisionShape,
		TConstArrayView<FTransform> InTransforms)
	: FPrimitiveSceneProxy(InComponent)
	, Shape(InCollisionShape)
	, Transforms(InTransforms)
	{
		
	}
	
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views,
									   const FSceneViewFamily& ViewFamily,
									   uint32 VisibilityMap,
									   FMeshElementCollector& Collector) const override
	{
		
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bDynamicRelevance = true;
		Result.bEditorPrimitiveRelevance = true;
		return Result;
	}

	virtual uint32 GetMemoryFootprint() const override
	{
		return( sizeof( *this ) + GetAllocatedSize() );
	}

	uint32 GetAllocatedSize() const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

	virtual SIZE_T GetTypeHash() const override
	{
		static SIZE_T UniquePointer;
		return reinterpret_cast<SIZE_T>(&UniquePointer);
	}

	FCollisionShape Shape;
	TArray<FTransform> Transforms;
};

// Sets default values for this component's properties
UAnimPreviewDebugDrawComponent::UAnimPreviewDebugDrawComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FPrimitiveSceneProxy* UAnimPreviewDebugDrawComponent::CreateSceneProxy()
{
	return new FAnimPreviewDrawShapeProxy(this,Shape,Transforms);
}

FBoxSphereBounds UAnimPreviewDebugDrawComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	return Super::CalcBounds(LocalToWorld);
}

