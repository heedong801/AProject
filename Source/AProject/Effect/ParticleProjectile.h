// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Etc/CustomActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ParticleProjectile.generated.h"

UCLASS()
class APROJECT_API AParticleProjectile : public ACustomActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParticleProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* m_Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

		float	m_Distance;

	int32	m_Attack;
	ACharacter* m_Owner;

public:
	virtual void SetActiveBullet(FVector Dir);
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}

	void SetProjectileOwner(class ACharacter* Actor)
	{
		m_Owner = Actor;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void ProjectileStop(const FHitResult& result);

protected:
	virtual void StopEvent(const FHitResult& result);
	virtual void SetActive(bool bOnActive);
};
