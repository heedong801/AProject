// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"
#include "../Buliding/Nexus.h"
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

	AActor* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target)
	{
		Target = Cast<ANexus>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetBuliding")));
		if (!Target)
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

	float	CapsuleHalfHeight = Monster->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float	CapsuleRadius = Monster->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	//LOG(TEXT("Capsule  hf, Rad : %f %f"), CapsuleHalfHeight, CapsuleRadius);

	MonsterLoc.Z = PatrolPoint.Z;
	float	Distance = FVector::Distance(MonsterLoc, PatrolPoint);
	//LOG(TEXT("PatrolPoint : %f %f %f"), PatrolPoint.X, PatrolPoint.Y, PatrolPoint.Z);
	//LOG(TEXT("MonsterLoc : %f %f %f"), MonsterLoc.X, MonsterLoc.Y, MonsterLoc.Z);
	//LOG(TEXT("%f %f"), Distance, CapsuleRadius + 5);

	m_AccTime += DeltaSeconds;


			 
	if (Distance <= CapsuleRadius + 7 || m_AccTime >= m_WaitTime)
	{
		//LOG(TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAA"), Distance);

		m_AccTime = 0.f;
		Monster->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}



