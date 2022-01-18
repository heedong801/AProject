// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueFlyProjectile.h"
#include "NormalEffect.h"
#include "../Monster/Monster.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
// Sets default values
ABlueFlyProjectile::ABlueFlyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/ParagonMinions/FX/Particles/Buffs/Buff_Blue/FX/P_Spit_Attack_Projectile.P_Spit_Attack_Projectile'"));

	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	m_Movement->ProjectileGravityScale = 0.5f;
	m_Movement->InitialSpeed = 1000.f;

	m_Body->SetCollisionProfileName(TEXT("EnemyAttackObj"));

	m_Particle->bAutoActivate = false;
}

void ABlueFlyProjectile::StopEvent(const FHitResult& result)
{
	//LOG(TEXT("AA"));
	Super::StopEvent(result);

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(result.ImpactPoint, result.Normal.Rotation(), ANormalEffect::StaticClass()));
	
	//LOG(TEXT("%s"), *result.GetActor()->GetName());
	if (Effect != nullptr)
	{
		Effect->LoadParticleAsync(TEXT("Buff_Blue_Impact"));
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
	}

	m_Particle->SetActive(false);
	m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActive(false);
}

void ABlueFlyProjectile::SetActiveBullet(FVector HitDirection)
{
	//m_Movement->SetActive(true);
	//m_Movement->SetVelocityInLocalSpace(FVector(1000.f, 0.f, 0.f));
	m_Body->SetCollisionProfileName(TEXT("EnemyAttackObj"));
	m_Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_Movement->SetUpdatedComponent(m_Body);
	m_Particle->SetActive(true);
	m_Particle->SetHiddenInGame(false);
	
	m_Movement->Velocity = HitDirection * m_Movement->InitialSpeed;
	//LOG(TEXT("%f %f %f"), m_Movement->Velocity.X, m_Movement->Velocity.Y, m_Movement->Velocity.Z);
}

void ABlueFlyProjectile::SetActive(bool bOnActive)
{
	Super::SetActive(bOnActive);
	//LOG(TEXT("Blue SetActive"));
	if (bOnActive)
	{
		m_Body->SetCollisionProfileName(TEXT("EnemyAttackObj"));

	}
	else
	{
		m_Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
}