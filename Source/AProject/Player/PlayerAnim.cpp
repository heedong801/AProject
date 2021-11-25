#pragma once
#include"PlayerAnim.h"
#include"PlayerCharacter.h"
#include "../DebugClass.h"
UPlayerAnim::UPlayerAnim()
	: m_Dir(0), m_Speed(0), m_CanAttack(true), m_OnSky(false)
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
	
	//LOG(TEXT("%f"), Player->GetActorScale3D().Size());
	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (Movement)
		{
			m_Speed = Movement->Velocity.Size();

			m_OnSky = Movement->IsFalling();
			if (!m_OnSky)
			{
				m_DoubleJump = false;
				ChangeAnimType(EPlayerAnimType::Ground);
			}
			else
				ChangeAnimType(EPlayerAnimType::Sky);

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

