// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticleProjectile.h"
#include "BlueFlyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ABlueFlyProjectile : public AParticleProjectile
{
	GENERATED_BODY()
public:
	ABlueFlyProjectile();

	virtual void SetActiveBullet(FVector HitDirection);
protected:
	virtual void StopEvent(const FHitResult& result);


};
