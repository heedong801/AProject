// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlePool.h"
#include "../DebugClass.h"
#include "NormalEffect.h"
#include "BlueFlyProjectile.h"
#include "WukongAttackProjectile.h"
UParticlePool::UParticlePool()
{
	//LOG(TEXT("N : %d"), m_CustomActorArray.Num());
	//LOG(TEXT("M : %d"), m_CustomActorArrayMaxIdx);
	m_NormalEffectNum = 200;
	m_BlueFlyBulletArrayNum = 5;
	m_WukongBulletArrayNum = 10;
	m_CustomActorArrayMaxIdx = m_NormalEffectNum + m_BlueFlyBulletArrayNum + m_WukongBulletArrayNum;
	//LOG(TEXT("INSERT"));
	
}

UParticlePool::~UParticlePool()
{
}

void UParticlePool::MakePool()
{
	//LOG(TEXT("MAKEPOOL PARTICLE"));

	ACustomActor* Effect = nullptr;
	for (int32 i = 0; i < m_CustomActorArrayMaxIdx; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if( i < m_NormalEffectNum )
			Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < m_NormalEffectNum + m_BlueFlyBulletArrayNum)
			Effect = GetWorld()->SpawnActor<ABlueFlyProjectile>(ABlueFlyProjectile::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < m_CustomActorArrayMaxIdx)
			Effect = GetWorld()->SpawnActor<AWukongAttackProjectile>(AWukongAttackProjectile::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);

		if (Effect)
		{
			Effect->SetActive(false);
			m_CustomActorArray.Add(Effect);
		}
	}

	
}


int UParticlePool::GetSize()
{
	return m_CustomActorArray.Num(); 
}

ACustomActor* UParticlePool::Pop(FVector Pos, FRotator Rot, UClass* Type)
{
	if (this != nullptr && IsValid(this))
	{
		LOG(TEXT("POP"));
		int32 Start = 0, End = m_CustomActorArrayMaxIdx;
		//int32 ParticleIdx = -1;
		if (Type == ANormalEffect::StaticClass())
		{
			Start = 0;
			End = m_NormalEffectNum;
			//ParticleIdx = 0;
		}
		else if (Type == ABlueFlyProjectile::StaticClass())
		{
			Start = m_NormalEffectNum;
			End = m_NormalEffectNum + m_BlueFlyBulletArrayNum;
			//ParticleIdx = 1;
		}
		else if (Type == AWukongAttackProjectile::StaticClass())
		{
			Start = m_NormalEffectNum + m_BlueFlyBulletArrayNum;
			End = m_CustomActorArrayMaxIdx;
			//ParticleIdx = 2;
		}

		for (int32 i = Start; i < End; ++i)
		{
			if (m_CustomActorArray[i] != nullptr && IsValid(m_CustomActorArray[i]))
			{
				if (m_CustomActorArray[i]->GetActive() == false)
				{
					m_CustomActorArray[i]->SetActive(true);
					m_CustomActorArray[i]->SetActorLocation(Pos);
					m_CustomActorArray[i]->SetActorRotation(Rot);
					
					LOG(TEXT("GOOD : %d"), i);
					return m_CustomActorArray[i];
				}
			}

		}
	}
	LOG(TEXT("FALSS"));
	return nullptr;

}