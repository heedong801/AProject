// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"
#include "../Buliding/Nexus.h"
UBTDecorator_CheckDistance::UBTDecorator_CheckDistance()
{
	NodeName = TEXT("CheckDistance");
}

bool UBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	
	if (!Controller)
		return false;
	
	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return false;

	AActor* Target = Cast<APlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target)
	{
		Target = Cast<ANexus>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetBuliding")));
		if( !Target )
			return false;
	}
		

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	// Ÿ�ٰ��� �Ÿ�
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	float CheckDist = 0.f;

	LOG(TEXT("%f"), Distance);
	LOG(TEXT("%f"), CheckDist);

	switch (m_CheckType)
	{
	case ECheckDistanceType::Trace:
		CheckDist = MonsterInfo.TraceDistance;
		break;
	case ECheckDistanceType::Attack:
		CheckDist = MonsterInfo.AttackDistance;
		break;
	}


	return Distance <= CheckDist;
}
