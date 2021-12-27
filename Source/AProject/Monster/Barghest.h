// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "Barghest.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ABarghest : public AMonster
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	ABarghest();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void NormalAttack();
	virtual void Death();
};