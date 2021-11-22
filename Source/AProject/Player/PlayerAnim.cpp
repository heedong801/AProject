#pragma once
#include"PlayerAnim.h"
#include"PlayerCharacter.h"
#include "../DebugClass.h"
UPlayerAnim::UPlayerAnim()
	: m_Dir(0), m_Speed(0), m_CanAttack(true)
{

}

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());
	
	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (Movement)
		{
			m_Speed = Movement->Velocity.Size();

			bool OnGround = Movement->IsMovingOnGround();
			//�� �ȹ�� �ִٰ� ������ ������ ������
			/*if (!m_OnGround && OnGround && Player->IsMoveKey())
				m_AnimType = EPlayerAnimType::Ground;*/

			//m_OnGround = OnGround;
			//�� �ȹ�� �ְ�, ������ �ƴѰ�� = �������� ���
			/*if (!m_OnGround && m_AnimType != EPlayerAnimType::Jump)
				m_AnimType = EPlayerAnimType::Fall;*/
			//m_OnGround = Movement->IsMovingOnGround();

		}
	}
}

void UPlayerAnim::AnimNotify_AttackCombo()
{
	m_CanAttack = true;
}

void UPlayerAnim::AnimNotify_HitDamage()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->HitDamage();
}

FName UPlayerAnim::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UPlayerAnim::SetFullbody(float useFullbody)
{
	if (useFullbody > 0.f)
		m_UseFullbody = true;
	else
		m_UseFullbody = false;
}
