// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetTrace.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"
#include "../Building/Nexus.h"
UBTTask_TargetTrace::UBTTask_TargetTrace()
{
	NodeName = TEXT("TargetTrace");
	bNotifyTick = true;

}

UBTTask_TargetTrace::~UBTTask_TargetTrace()
{

}

EBTNodeResult::Type UBTTask_TargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//PrintViewport(1.0f, FColor::Red, TEXT("ExecuteTask"));
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return EBTNodeResult::Failed;
	

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return EBTNodeResult::Failed;
	


	UObject* uO = Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
	AActor* Target = Cast<APlayerCharacter>(uO);
	if (!Target)
	{
		Target = Cast<ANexus>(uO);
		if (!Target)
		{
			Monster->ChangeAnimType(EMonsterAnimType::Idle);

			Controller->StopMovement();
			return EBTNodeResult::Failed;
		}
	}


	

	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MoveSpeed;

	//UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	Monster->ChangeAnimType(EMonsterAnimType::Walk);
	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTTask_TargetTrace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);


	return result;
}

void UBTTask_TargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//PrintViewport(1.0f, FColor::Red, TEXT("TickTask"));

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//PrintViewport(1.0f, FColor::Red, TEXT("TRACE"));
	//InProgress로 체크해두었기 때문에 여기서안나간다.
	// 그래서 공격거리 안에 들어있는지를 여기서도 체크하여 들어갔다면
	//Trace를 종료시킨다.


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
	float TargetHalfCapsuleRadius;

	if (!Target)
	{
		Target = Cast<ANexus>(uO);
		if (!Target)
		{
			Monster->ChangeAnimType(EMonsterAnimType::Idle);

			Controller->StopMovement();

			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
		else
		{
			ANexus* TargetActor = Cast<ANexus>(uO);
			TargetHalfCapsuleRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.5f;
		}
	}
	else
	{
		APlayerCharacter* TargetActor = Cast<APlayerCharacter>(uO);
		TargetHalfCapsuleRadius = TargetActor->GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.5f;
	}


	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	//LOG(TEXT("A"));
	float ZGapToTarget = FMath::Abs(Target->GetActorLocation().Z - Monster->GetActorLocation().Z);
	FVector TargetLoc = Target->GetActorLocation();
	//LOG(TEXT("%f"), ZGapToTarget);



	//LOG(TEXT("C : %f %f %f"), TargetLoc.X, TargetLoc.Y, TargetLoc.Z);

	if (TargetLoc.Z >= Monster->GetActorLocation().Z)
		TargetLoc.Z -= ZGapToTarget * 0.0f;
	else
		TargetLoc.Z += ZGapToTarget * 0.0f;

	EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(TargetLoc);

	if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		//LOG(TEXT("AlreadyAtGoal"));
	}
	else if (Result == EPathFollowingRequestResult::Failed)
	{
		//LOG(TEXT("Failed"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;

	}
	else
	{
		//LOG(TEXT("RequestSuccessful"));
	}

	// 타겟과의 거리
	FVector MonsterLoc = Monster->GetActorLocation();
	float MonsterHalfCapsuleRadius = Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.5f;

	MonsterLoc.Z = TargetLoc.Z;
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	Distance -= (MonsterHalfCapsuleRadius + TargetHalfCapsuleRadius);

	float Offset = 55;
	Distance -= Offset;

	//LOG(TEXT("D : %f"), Distance);
	if (Distance <= MonsterInfo.AttackDistance)
	{
		//LOG(TEXT("C"));

		Controller->StopMovement();
		//Controller->SetActorRotation(FQuat::))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}