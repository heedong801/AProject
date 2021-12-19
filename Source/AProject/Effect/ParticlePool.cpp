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
	m_NormalEffectNum = 300;
	m_BlueFlyBulletArrayNum = 5;
	m_WukongBulletArrayNum = 10;
	m_CustomActorArrayMaxIdx = m_NormalEffectNum + m_BlueFlyBulletArrayNum + m_WukongBulletArrayNum;
	//LOG(TEXT("INSERT"));
	
}

UParticlePool::~UParticlePool()
{
	/*LOG(TEXT("%d"), m_CustomActorArray.Num());
	m_CustomActorArray.RemoveAll([](NormalEffect* e) {return true; });
	LOG(TEXT("%d"), m_CustomActorArray.Num());*/
	//LOG(TEXT("DELETE"));

}

void UParticlePool::MakePool()
{
	for (int32 i = 0; i < m_NormalEffectNum; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		Effect->SetActive(false);
		m_CustomActorArray.Add(Effect);
	}
	for (int32 i = 0; i < m_BlueFlyBulletArrayNum; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABlueFlyProjectile* Effect = GetWorld()->SpawnActor<ABlueFlyProjectile>(ABlueFlyProjectile::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		Effect->SetActive(false);
		m_CustomActorArray.Add(Effect);
	}
	for (int32 i = 0; i < m_WukongBulletArrayNum; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AWukongAttackProjectile* Effect = GetWorld()->SpawnActor<AWukongAttackProjectile>(AWukongAttackProjectile::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		Effect->SetActive(false);
		m_CustomActorArray.Add(Effect);
	}
	//LOG(TEXT("MN : %d"), m_CustomActorArray.Num());
	//LOG(TEXT("MM : %d"), m_CustomActorArrayMaxIdx);
}


int UParticlePool::GetSize()
{
	return m_CustomActorArray.Num(); 
}

ACustomActor* UParticlePool::Pop(FVector Pos, FRotator Rot, UClass* Type)
{
	if (this != nullptr && IsValid(this))
	{
		//LOG(TEXT("POP"));
		int32 Start = 0, End = m_CustomActorArrayMaxIdx;

		if (Type == ANormalEffect::StaticClass())
		{
			Start = 0;
			End = m_NormalEffectNum;
		}
		else if (Type == ABlueFlyProjectile::StaticClass())
		{
			Start = m_NormalEffectNum;
			End = m_NormalEffectNum + m_BlueFlyBulletArrayNum;
		}
		else if (Type == AWukongAttackProjectile::StaticClass())
		{
			Start = m_NormalEffectNum + m_BlueFlyBulletArrayNum;
			End = m_CustomActorArrayMaxIdx;
		}

		for (int32 i = Start; i < End; ++i)
		{
			if (m_CustomActorArray[i] != nullptr)
			{
				if (m_CustomActorArray[i]->GetActive() == false)
				{
					m_CustomActorArray[i]->SetActive(true);
					m_CustomActorArray[i]->SetActorLocation(Pos);
					m_CustomActorArray[i]->SetActorRotation(Rot);

					return m_CustomActorArray[i];
				}
			}

		}

		return nullptr;
	}
	return nullptr;

}