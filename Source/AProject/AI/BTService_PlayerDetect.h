// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PlayerDetect.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UBTService_PlayerDetect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerDetect();

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
