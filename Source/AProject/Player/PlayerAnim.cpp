#pragma once
#include"PlayerAnim.h"
#include"PlayerCharacter.h"
#include "../DebugClass.h"
#include "../Effect/NormalEffect.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "../AProjectGameInstance.h"
#include "../Player/Wukong.h"
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
			//LOG(TEXT("%f"), m_Speed);
			m_OnSky = Movement->IsFalling();

			//LOG(TEXT("%f"), Player->GetCharacterMovement()->GravityScale);
			//LOG(TEXT("%f"), Player->GetCharacterMovement()->JumpZVelocity);

			if (!m_OnSky)
			{
				m_DoubleJump = false;
				ChangeAnimType(EPlayerAnimType::Ground);
				//Player->GetCharacterMovement()->GravityScale = 1.f;

			}
			else
			{
				ChangeAnimType(EPlayerAnimType::Sky);


				//Player->GetCharacterMovement()->GravityScale = 3.f;
			}

		}
	}
}

void UPlayerAnim::AnimNotify_AttackCombo()
{
	//LOG(TEXT("true : %s"), *GetSkelMeshComponent()->GetName());


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

void UPlayerAnim::AnimNotify_AddGravity()
{
	//LOG(TEXT("AnimNotify_AddGravity"));
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());
	
	if (Player)
	{
		Player->SetTimeDillation();
		Player->GetCharacterMovement()->Velocity.X = 0.f;
		Player->GetCharacterMovement()->Velocity.Y = 0.f;
		//Player->SetActorLocation( FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, Player->GetActorLocation().Z + 200)) ;

		GetWorld()->GetTimerManager().SetTimer(m_AddGravityTimer,
			this, &UPlayerAnim::AddGravity, 1.f, false, 0.1f);
		//Player->GetCharacterMovement()->Velocity.Z = 0.f;
		//Player->GetCharacterMovement()->GravityScale = 200.0f;
		//LOG(TEXT("%f %f %f"), Player->GetCharacterMovement()->Velocity.X, Player->GetCharacterMovement()->Velocity.Y, Player->GetCharacterMovement()->Velocity.Z);
	}
}

void UPlayerAnim::AddGravity()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (Player)
		Player->GetCharacterMovement()->GravityScale = 200.0f;

}


void UPlayerAnim::AnimNotify_SlamEnd()
{
	//LOG(TEXT("AnimNotify_SlamEnd"));

	AWukong* Wukong = Cast<AWukong>(TryGetPawnOwner());
	Wukong->SlamDamage();
}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	//LOG(TEXT("true : %s"), *GetSkelMeshComponent()->GetName());

	m_CanAttack = true;

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->SetCurrentCombo(0);
		Player->SetMovable(true);
		Player->CameraArmYawReset();
		
		AWukong* Wukong = Cast<AWukong>(Player);
		if (Wukong)
			Wukong->SetCanAttack();

	}


}


void UPlayerAnim::AnimNotify_UseSkill()
{

	m_CanAttack = false;
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player )
	{
		//LOG(TEXT("C"));
		Player->SetMovable(false);

		Player->UseSkill(Player->GetSkillIdx());
	}
}
