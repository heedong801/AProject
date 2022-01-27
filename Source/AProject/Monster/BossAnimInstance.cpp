// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{
	//m_AnimType = EMonsterAnimType::Idle;

}

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


}

void UBossAnimInstance::AnimNotify_HitAttack()
{
	/*AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->NormalAttack();*/
}

void UBossAnimInstance::AnimNotify_AttackEnd()
{
	/*AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->SetAttackEnd(true);*/
}



void UBossAnimInstance::AnimNotify_HitEnd()
{
	//m_Hit = 0.f;
}

