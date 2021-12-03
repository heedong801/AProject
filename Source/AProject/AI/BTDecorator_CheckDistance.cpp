// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterAIController.h"
#include "../DebugClass.h"
#include "../Building/Nexus.h"
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

	UObject* uO = Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));
	AActor* Target = Cast<APlayerCharacter>(uO);
	float TargetHalfCapsuleRadius;
	if (!Target)
	{
		Target = Cast<ANexus>(uO);
		if (!Target)
			return false;
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

	// 타겟과의 거리
	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();
	float MonsterHalfCapsuleRadius = Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() * 0.5f;


	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);
	float CheckDist = 0.f;
	//LOG(TEXT("A : Distance : %f"), Distance);
	
	Distance -= (MonsterHalfCapsuleRadius + TargetHalfCapsuleRadius);
	
	float Offset = 55;
	Distance -= Offset;

	//Controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);

	//LOG(TEXT("%f"), Distance);

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
