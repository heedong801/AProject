// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"
#include "../Building/Nexus.h"
UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;

	m_AccTime = 0.f;
	m_WaitTime = 5.f;
}


EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//PrintViewport(1.0f, FColor::Red, TEXT("ExecuteTask"));
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());


	if (!Controller)
		return EBTNodeResult::Failed;


	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->ChangeAnimType(EMonsterAnimType::Walk);
	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MoveSpeed * 0.7f;
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());
	//Monster->SetPatrolEnable(true);
	
	
	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTTask_Patrol::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);


	return result;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//PrintViewport(1.0f, FColor::Red, TEXT("TickTask"));

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//PrintViewport(1.0f, FColor::Red, TEXT("TRACE"));
	//InProgress�� üũ�صξ��� ������ ���⼭�ȳ�����.
	// �׷��� ���ݰŸ� �ȿ� ����ִ����� ���⼭�� üũ�Ͽ� ���ٸ�
	//Trace�� �����Ų��.

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	UObject* uO = Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));

	AActor* Target = Cast<APlayerCharacter>(uO);
	if (!Target)
	{
		Target = Cast<ANexus>(uO);
		if (Target)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}


	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	
	// �����ߴٸ�.
	FVector	PatrolPoint = Monster->GetPatrolPoint();
	FVector	MonsterLoc = Monster->GetActorLocation();

	float	CapsuleRadius = Monster->GetCapsuleComponent()->GetUnscaledCapsuleRadius();

	MonsterLoc.Z = PatrolPoint.Z;

	float	Distance = FVector::Distance(MonsterLoc, PatrolPoint);
	Distance -= CapsuleRadius;
	LOG(TEXT("PatrolPoint : %f %f %f"), PatrolPoint.X, PatrolPoint.Y, PatrolPoint.Z);
	//LOG(TEXT("MonsterLoc : %f %f %f"), MonsterLoc.X, MonsterLoc.Y, MonsterLoc.Z);
	//LOG(TEXT("%f"), Distance );

	m_AccTime += DeltaSeconds;

	int Offset = Monster->GetMonsterInfo().DistanceOffset;
	if (Distance <= Offset || m_AccTime >= m_WaitTime)
	{
		//LOG(TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAA"), Distance);

		m_AccTime = 0.f;
		Monster->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}



