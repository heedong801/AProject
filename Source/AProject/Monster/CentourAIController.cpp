// Fill out your copyright notice in the Description page of Project Settings.


#include "CentourAIController.h"


ACentourAIController::ACentourAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Centour/BT_Centour.BT_Centour'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void ACentourAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACentourAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
