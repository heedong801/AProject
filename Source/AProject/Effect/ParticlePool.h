// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NormalEffect.h"
#include "../Etc/CustomActor.h"
#include "ParticlePool.generated.h"


UCLASS()
class APROJECT_API UParticlePool : public UObject
{
	GENERATED_BODY()

protected:
	TArray<ACustomActor*> m_CustomActorArray;
	int32 m_CustomActorArrayMaxIdx;

public:
	UParticlePool();
	~UParticlePool();

	void MakePool();
	int GetSize();
	
	ACustomActor* Pop(FVector Pos, FRotator Rot);
};
