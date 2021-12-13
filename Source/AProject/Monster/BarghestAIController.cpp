// Fill out your copyright notice in the Description page of Project Settings.


#include "BarghestAIController.h"
#include "../DebugClass.h"

ABarghestAIController::ABarghestAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Barghest/BT_Barhest.BT_Barhest'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void ABarghestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABarghestAIController::OnUnPossess()
{
	Super::OnUnPossess();
}


