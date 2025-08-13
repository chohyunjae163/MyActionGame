#pragma once

#include "ActionGameShapeParam.generated.h"


// hjcho:
// note: ECollisionShape::Type 과 순서를 맞춤.
UENUM(BlueprintType,DisplayName=ShapeType)
enum class EActionGameShapeType : uint8
{
	Line    UMETA(Hidden),
	Box     UMETA(DisplayName="Box"),
	Sphere  UMETA(DisplayName="Sphere"),
	Capsule UMETA(DisplayName="Capsule")
};


USTRUCT(BlueprintType)
struct FCapsuleParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HalfHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 0.f;

};

USTRUCT(BlueprintType)
struct FSphereParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 0.f;
	
};

USTRUCT(BlueprintType)
struct FBoxParams
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HalfExtent = FVector::ZeroVector;
	
};

USTRUCT(BlueprintType)
struct FActionGameShape
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EActionGameShapeType Type = EActionGameShapeType::Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="Type==EActionGameShapeType::Capsule"))
	FCapsuleParams Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="Type==EActionGameShapeType::Sphere"))
	FSphereParams Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="Type==EActionGameShapeType::Box"))
	FBoxParams Box;

	// 헬퍼: 현재 타입에 맞는 데이터를 꺼내오는 함수들
	FCollisionShape ToCollisionShape() const
	{
		switch (Type)
		{
		case EActionGameShapeType::Box:
			return FCollisionShape::MakeBox(Box.HalfExtent);
		case EActionGameShapeType::Capsule:
			return FCollisionShape::MakeCapsule(Capsule.Radius, Capsule.HalfHeight);
		case EActionGameShapeType::Sphere:
			return FCollisionShape::MakeSphere(Sphere.Radius);
		default:
			return FCollisionShape();
		}
	}
};