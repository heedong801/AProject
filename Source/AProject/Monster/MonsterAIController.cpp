// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../DebugClass.h"
AMonsterAIController::AMonsterAIController()
{

}
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//�����带 �����Ѵ�.
	if (UseBlackboard(m_AIBlackboard, Blackboard))
	{
		//�ൿƮ���� ���۽�Ų��.
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

void AMonsterAIController::StartAI()
{
	if (UseBlackboard(m_AIBlackboard, Blackboard))
	{
		RunBehaviorTree(m_AITree);
	}
}

void AMonsterAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}