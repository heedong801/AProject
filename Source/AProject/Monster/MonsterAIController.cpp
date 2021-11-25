// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../DebugClass.h"
AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/BT_Shoebill.BT_Shoebill'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardAsset(TEXT("BlackboardData'/Game/Monster/BB_Monster.BB_Monster'"));

	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//블랙보드를 지정한다.
	if (UseBlackboard(m_AIBlackboard, Blackboard))
	{
		//행동트리를 동작시킨다.
		if (!RunBehaviorTree(m_AITree))
		{
			LOG(TEXT("Monster BehaviorTree Error"));
		}
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}