// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"

UBTTask_NormalAttack::UBTTask_NormalAttack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;

}


EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return EBTNodeResult::Failed;


	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return EBTNodeResult::Failed;

	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target)
	{
		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();
		return EBTNodeResult::Failed;
	}

	int randomAttack = FMath::RandRange(0, 2);
	switch (randomAttack)
	{
	case 0:
		Monster->ChangeAnimType(EMonsterAnimType::Attack1);
		break;
	case 1:
		Monster->ChangeAnimType(EMonsterAnimType::Attack2);
		break;
	case 2:
		Monster->ChangeAnimType(EMonsterAnimType::Attack3);
		break;
	}


	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTTask_NormalAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);


	return result;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//PrintViewport(1.0f, FColor::Red, TEXT("TRACE"));
	//InProgress로 체크해두었기 때문에 여기서

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


	APlayerCharacter* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target)
	{

		Monster->ChangeAnimType(EMonsterAnimType::Idle);
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	// 타겟과의 거리
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	//PrintViewport(1.0f, FColor::Red, TEXT("NormalAttack.cpp"));


	if (Monster->GetAttackEnd())
	{
		//PrintViewport(1.0f, FColor::Red, TEXT("AttackEnd.cpp"));

		if (Distance > MonsterInfo.AttackDistance)
		{
			//PrintViewport(1.0f, FColor::Red, TEXT("TraceStart.cpp"));

			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			//return;
		}
		else
		{
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();

			FRotator TargetRot = FRotator(0.f, Dir.Rotation().Yaw, 0.f);
			Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(),
				TargetRot, GetWorld()->GetDeltaSeconds(), 200.0f));
		}
		//PrintViewport(1.0f, FColor::Red, TEXT("End.cpp"));

		Monster->SetAttackEnd(false);
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}

