// Fill out your copyright notice in the Description page of Project Settings.


#include "WukongAttackProjectile.h"
#include "NormalEffect.h"
#include "../Monster/Monster.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
// Sets default values
AWukongAttackProjectile::AWukongAttackProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_fire_Attack.P_ky_shot_fire_Attack'"));

	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	m_Particle->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	m_Movement->ProjectileGravityScale = 0.f;
	m_Movement->InitialSpeed = 2500.f;

	m_Body->SetCollisionProfileName(TEXT("PlayerAttackObj"));

	m_Particle->bAutoActivate = false;

}

void AWukongAttackProjectile::SetActive(bool bOnFlag)
{
	Super::SetActive(bOnFlag);

	GetWorld()->GetTimerManager().SetTimer(SetFalseTimerHandle, this, &AWukongAttackProjectile::SetFalse, 3.0f, false, -1.f);

	if (bOnFlag) 
	{
		m_Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}
void AWukongAttackProjectile::StopEvent(const FHitResult& result)
{
	//LOG(TEXT("%s"), *result.GetActor()->GetName());
	Super::StopEvent(result);

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(result.ImpactPoint, result.Normal.Rotation(), ANormalEffect::StaticClass()));

	FCollisionQueryParams params(NAME_None, false, this);

	TArray<FHitResult> HitResultArray;
	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
		, FCollisionShape::MakeSphere(500.f), params);

	//LOG(TEXT("%s"), *result.GetActor()->GetName());
	if (Effect != nullptr)
	{
		Effect->LoadParticleAsync(TEXT("Saga_Fire"));
	}

	//m_Movement->InitialSpeed = 0.f;
	//LOG(TEXT("S :%f %f %f"), m_Movement->Velocity.X, m_Movement->Velocity.Y, m_Movement->Velocity.Z);
	//m_Movement->Velocity = FVector()
	//LOG(TEXT("%f %f %f"), m_Movement->Velocity.X, m_Movement->Velocity.Y, m_Movement->Velocity.Z);
	//LOG(TEXT("%s"), *m_Owner->GetName());

	if (IsValid(m_Owner))
	{
		FDamageEvent	DmgEvent;
		result.GetActor()->TakeDamage(m_Attack, DmgEvent,
			m_Owner->GetController(), m_Owner);

		for (auto resultActor : HitResultArray)
		{
			if (Sweep)
				resultActor.GetActor()->TakeDamage(m_Attack, DmgEvent, m_Owner->GetController(), m_Owner);
			
		}
	}

	m_Particle->SetActive(false);
	m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActive(false);
}

void AWukongAttackProjectile::SetActiveBullet(FVector HitDirection)
{
	//m_Movement->SetActive(true);
	//m_Movement->SetVelocityInLocalSpace(FVector(1000.f, 0.f, 0.f));
	m_Body->SetCollisionProfileName(TEXT("PlayerAttackObj"));
	m_Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_Movement->SetUpdatedComponent(m_Body);
	m_Particle->SetActive(true);
	m_Particle->SetHiddenInGame(false);

	m_Movement->Velocity = HitDirection * m_Movement->InitialSpeed;
	//LOG(TEXT("%f %f %f"), m_Movement->Velocity.X, m_Movement->Velocity.Y, m_Movement->Velocity.Z);
}


void AWukongAttackProjectile::SetFalse()
{
	SetActive(false);
}

