// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Wukong.generated.h"

UCLASS()
class APROJECT_API AWukong : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWukong();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual int32 GetCurrentCombo() { return m_CurrentCombo; }
	virtual void SetCurrentCombo(int32 curCombo);
	virtual void HitDamage();

private:
	int32 m_MaxCombo;
	int32 m_CurrentCombo;



};
