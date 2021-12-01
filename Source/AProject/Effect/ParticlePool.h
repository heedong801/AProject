// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NormalEffect.h"
#include "ParticlePool.generated.h"


UCLASS()
class APROJECT_API UParticlePool : public UObject
{
	GENERATED_BODY()

protected:
	TArray<ANormalEffect*> m_NormalEffectArray;
	int32 m_NormalEffectArrayMaxIdx;


public:
	UParticlePool();
	~UParticlePool();

	void MakePool();
	int GetSize();
	
	ANormalEffect* Pop(FVector Pos, FRotator Rot);
};
