// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Etc/CustomActor.h"
#include "ParticlePool.generated.h"


UCLASS()
class APROJECT_API UParticlePool : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<ACustomActor*> m_CustomActorArray;
	UPROPERTY()
	int32 m_CustomActorArrayMaxIdx;
	UPROPERTY()
	int32 m_NormalEffectEnd;
	UPROPERTY()
	int32 m_BlueFlyBulletArray;
public:
	UParticlePool();
	~UParticlePool();

	void MakePool();
	int GetSize();
	
	ACustomActor* Pop(FVector Pos, FRotator Rot, UClass* Type);

	int32 GetNormalEffectEndIdx() { return m_NormalEffectEnd;  }
	int32 GetParticleProjectileEndIdx() { return m_BlueFlyBulletArray; }

};
