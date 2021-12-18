// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticleProjectile.h"
#include "WukongAttackProjectile.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AWukongAttackProjectile : public AParticleProjectile
{
	GENERATED_BODY()
public:
	AWukongAttackProjectile();

	virtual void SetActive(bool);
	void SetFalse();
	virtual void SetActiveBullet(FVector HitDirection);
protected:
	virtual void StopEvent(const FHitResult& result);

private:
	FTimerHandle SetFalseTimerHandle;
};
