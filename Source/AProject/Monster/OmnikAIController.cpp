// Fill out your copyright notice in the Description page of Project Settings.


#include "OmnikAIController.h"

AOmnikAIController::AOmnikAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Omnik/BT_Omnik.BT_Omnik'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void AOmnikAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AOmnikAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
