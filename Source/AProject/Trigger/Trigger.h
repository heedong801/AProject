// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Trigger.generated.h"

UENUM(BlueprintType)
enum class ETriggerType : uint8
{
	Box,
	Capsule,
	Sphere
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS(BlueprintType)
class APROJECT_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UShapeComponent* m_Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ETriggerType m_ShapeType;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FTriggerDelegate m_TriggerBeginDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FTriggerDelegate m_TriggerEndDelegate;
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
	UFUNCTION()
		void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	FTriggerDelegate& GetBeginDelegate()
	{
		return m_TriggerBeginDelegate;
	}

	FTriggerDelegate& GetEndDelegate()
	{
		return m_TriggerEndDelegate;
	}
	// FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex
};
