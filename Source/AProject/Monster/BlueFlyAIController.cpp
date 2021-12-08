// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueFlyAIController.h"
#include "../DebugClass.h"

ABlueFlyAIController::ABlueFlyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/BlueFly/BT_BlueFly.BT_BlueFly'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void ABlueFlyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABlueFlyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

