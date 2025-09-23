// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interface/DamageCauserInterface.h"
#include "MeleeAttackTraceComponent.generated.h"


USTRUCT()
struct FMeleeAttackCapsuleTraceData
{
	GENERATED_BODY()
	float		CapsuleHalfHeight;
	float		CapsuleRadius;
	FVector		CapsuleCenter;
	FRotator	CapsuleRotation;
};

/*
	근접 공격 충돌을 트레이스 하는 컴포넌트.
*/
UCLASS(MinimalAPI, ClassGroup=(ActionGame), meta=(BlueprintSpawnableComponent) )
class UMeleeAttackTraceComponent : public UPawnComponent,public IDamageCauserInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeAttackTraceComponent(const FObjectInitializer& ObjectInitializer);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	// begin IDamageCauserInterface
	virtual class UAbilitySystemComponent* GetMyAbilitySystemComponent() const override;
	virtual TObjectPtr<APawn> GetDamageCauserPawn() const override;
	// end IDamageCauserInterface
	
	void OnAnimMeleeAttackMessage(struct FGameplayTag Channel, const struct FMeleeAttackMessage& Message);
private:
	TQueue<FTransform>				Transforms;
	FCollisionShape					CollisionShape;
	FGameplayMessageListenerHandle	ListenerHandle;

};

