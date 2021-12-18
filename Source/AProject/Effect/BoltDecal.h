// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectDecal.h"
#include "BoltDecal.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ABoltDecal : public AEffectDecal
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoltDecal();

	virtual void Tick(float DeltaTime) override;

	void SetSkillOn(bool OnSkill) { m_SkillOn = OnSkill; }
	bool GetSkillOn() { return m_SkillOn; }
private:
	bool m_SkillOn;
};