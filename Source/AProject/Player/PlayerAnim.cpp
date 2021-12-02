#pragma once
#include"PlayerAnim.h"
#include"PlayerCharacter.h"
#include "../DebugClass.h"
#include "../Effect/NormalEffect.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "../AProjectGameInstance.h"
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
		Player->GetCharacterMovement()->Velocity.Z = 0.f;
		Player->GetCharacterMovement()->GravityScale = 200.0f;
		//LOG(TEXT("%f %f %f"), Player->GetCharacterMovement()->Velocity.X, Player->GetCharacterMovement()->Velocity.Y, Player->GetCharacterMovement()->Velocity.Z);
	}
}

void UPlayerAnim::AnimNotify_SlamEnd()
{
	//LOG(TEXT("AnimNotify_SlamEnd"));

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->SetTimeDillation();
		Player->GetCharacterMovement()->GravityScale = 1.0f;
		m_Attack = false;
		m_CanAttack = true;

		FCollisionQueryParams params(NAME_None, false, Player); 
	
		TArray<FHitResult> HitResultArray;
		bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, Player->GetActorLocation(), Player->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
			, FCollisionShape::MakeSphere(500.f), params);
		//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

#if ENABLE_DRAW_DEBUG
		FColor DrawColor = Sweep ? FColor::Red : FColor::Green;

		DrawDebugSphere(GetWorld(), Player->GetActorLocation(), 500, 20, DrawColor, false
			, 0.3f);

#endif
		FVector impactPoint = FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, Player->GetActorLocation().Z - 80.f);


		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			impactPoint, FRotator::ZeroRotator, param);
		Effect->LoadParticleAsync(TEXT("Slam1"));*/
		
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator);
		
		Effect->LoadParticleAsync(TEXT("Slam2"));
		
		ANormalEffect* Effect1 = GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator);
		Effect1->LoadParticleAsync(TEXT("Slam3"));


		for (auto result : HitResultArray)
		{
			if (Sweep)
			{
				//ANormalEffect* Effect3 = GameInst->GetParticlePool()->Pop(result.ImpactPoint, result.ImpactNormal.Rotation());

				//에셋 로딩
				//Effect3->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));
				//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
				//Effect3->LoadParticleAsync(TEXT("HitNormal"));
				//Effect->LoadSoundAsync(TEXT("HitNormal"));

				//데미지 전달
				FDamageEvent DmgEvent;
				float Damage = result.GetActor()->TakeDamage(150, DmgEvent, Player->GetController(), Player);
			}
		}
	}
}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	m_CanAttack = true;
	m_Attack = false;
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->SetCurrentCombo(0);
}

