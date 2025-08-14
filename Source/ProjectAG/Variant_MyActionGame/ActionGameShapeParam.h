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

	

	//
	bool ToCollisionShape(OUT FCollisionShape& Shape) const
	{
		switch (Type)
		{
		case EActionGameShapeType::Box:
			{
				if ( Box.HalfExtent.SquaredLength() <= KINDA_SMALL_NUMBER)
				{
					return false;
				}
				Shape =  FCollisionShape::MakeBox(Box.HalfExtent);
				break;
			}
			
		case EActionGameShapeType::Capsule:
			{
				if ( Capsule.Radius <= KINDA_SMALL_NUMBER || Capsule.HalfHeight <= KINDA_SMALL_NUMBER)
				{
					return false;
				}
				Shape = FCollisionShape::MakeCapsule(Capsule.Radius, Capsule.HalfHeight);
				break;
			}
			
		case EActionGameShapeType::Sphere:
			{
				if (Sphere.Radius <= KINDA_SMALL_NUMBER)
				{
					return false;
				}
				Shape = FCollisionShape::MakeSphere(Sphere.Radius);	
			}
			
			break;
		default:
			return false;
		}

		return true;
	}
};