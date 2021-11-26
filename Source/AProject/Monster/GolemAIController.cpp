// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemAIController.h"
#include "../DebugClass.h"

AGolemAIController::AGolemAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Golem/BT_Golem.BT_Golem'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void AGolemAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGolemAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
