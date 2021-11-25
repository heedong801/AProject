// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"

UBTService_PlayerDetect::UBTService_PlayerDetect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBTService_PlayerDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//LOG(TEXT("AA"));
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return;

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	// 주변에 플레이어가 있는지 판단한다.
	// ECC_GameTraceChannel6

	FCollisionQueryParams params(NAME_None, false, Monster); //몬스터제외
	// 근접 공격으로 이 타이밍에 충돌처리를 해주도록 한다. 
	FHitResult HitResult;
	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult, Monster->GetActorLocation(), Monster->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6
		, FCollisionShape::MakeSphere(MonsterInfo.TraceDistance), params);
	//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = Sweep ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(), MonsterInfo.TraceDistance, 20, DrawColor, false
	, 0.3f);

#endif
	if (Sweep)
	{
		//LOG(TEXT("BB"));

		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
	}
	else
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);

}