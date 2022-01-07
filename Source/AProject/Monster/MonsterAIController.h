// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIController();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_AITree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBlackboardData* m_AIBlackboard;
protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
public:
	virtual void StartAI();
	virtual void StopAI();
};
