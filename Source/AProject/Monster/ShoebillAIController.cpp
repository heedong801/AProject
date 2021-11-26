// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoebillAIController.h"
#include "../DebugClass.h"
AShoebillAIController::AShoebillAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/Shoebill/BT_Shoebill.BT_Shoebill'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;

}
void AShoebillAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AShoebillAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
