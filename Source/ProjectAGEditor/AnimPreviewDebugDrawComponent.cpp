// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPreviewDebugDrawComponent.h"

class FAnimPreviewDrawShapeProxy : public FPrimitiveSceneProxy
{
public:
	FAnimPreviewDrawShapeProxy(const UPrimitiveComponent* InComponent,
		const FCollisionShape& InCollisionShape,
		TConstArrayView<FTransform> InTransforms,
		const FLinearColor& InColor)
			: FPrimitiveSceneProxy(InComponent)
			, Shape(InCollisionShape)
			, Transforms(InTransforms)
			, DrawColor(InColor)
	{
		
	}
	
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views,
									   const FSceneViewFamily& ViewFamily,
									   uint32 VisibilityMap,
									   FMeshElementCollector& Collector) const override
	{
		static constexpr int32 NumSides = 24;
		static constexpr float Thickness = 0.25f;

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ++ViewIndex)
		{
			FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
			for (const FTransform& Transform : Transforms)
			{
				//a = Index / static_cast<float>(NumTransforms);
				//Color.R = Color.G = Color.B = a;
				const FVector UnitXAxis   = Transform.GetUnitAxis( EAxis::X );
				const FVector UnitYAxis   = Transform.GetUnitAxis( EAxis::Y );
				const FVector UnitZAxis   = Transform.GetUnitAxis( EAxis::Z );
				switch ( Shape.ShapeType )
				{
				case ECollisionShape::Line:
					break;
				case ECollisionShape::Box:
					break;
				case ECollisionShape::Sphere:
					break;
				case ECollisionShape::Capsule:
					const FVector CapsuleAdjust = UnitZAxis * Shape.GetCapsuleHalfHeight();
					const FVector BaseLocation = Transform.GetLocation() + CapsuleAdjust;
					DrawWireCapsule(
						PDI,
						BaseLocation,
						UnitXAxis,
						UnitYAxis,
						UnitZAxis,
						DrawColor,
						Shape.GetCapsuleRadius(),
						Shape.GetCapsuleHalfHeight(),
						NumSides,
						SDPG_World,
						Thickness
				);
					break;
				}
			}
		}
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
	FLinearColor DrawColor;
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
	return new FAnimPreviewDrawShapeProxy(this,Shape,Transforms,Color);
}

FBoxSphereBounds UAnimPreviewDebugDrawComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBoxSphereBounds NewBounds;
	NewBounds.Origin = FVector(0, 0, 0);
	NewBounds.BoxExtent = FVector(1000, 1000, 1000);
	NewBounds.SphereRadius = 1000;
	
	return NewBounds;
}

