// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlePool.h"
#include "../DebugClass.h"
#include "NormalEffect.h"
#include "BlueFlyProjectile.h"
UParticlePool::UParticlePool()
{
	//LOG(TEXT("N : %d"), m_CustomActorArray.Num());
	//LOG(TEXT("M : %d"), m_CustomActorArrayMaxIdx);
	m_NormalEffectEnd = 300;
	m_BlueFlyBulletArray = 2;
	m_CustomActorArrayMaxIdx = m_NormalEffectEnd + m_BlueFlyBulletArray;
}

UParticlePool::~UParticlePool()
{
	/*LOG(TEXT("%d"), m_CustomActorArray.Num());
	m_CustomActorArray.RemoveAll([](NormalEffect* e) {return true; });
	LOG(TEXT("%d"), m_CustomActorArray.Num());*/

}

void UParticlePool::MakePool()
{
	for (int32 i = 0; i < m_NormalEffectEnd; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		Effect->SetActive(false);
		m_CustomActorArray.Add(Effect);
	}
	for (int32 i = 0; i < m_BlueFlyBulletArray; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABlueFlyProjectile* Effect = GetWorld()->SpawnActor<ABlueFlyProjectile>(ABlueFlyProjectile::StaticClass(),
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

ACustomActor* UParticlePool::Pop(FVector Pos, FRotator Rot, UClass* Type )
{
	//LOG(TEXT("POP"));
	int32 Start = 0, End = m_CustomActorArrayMaxIdx;

	if (Type == ANormalEffect::StaticClass())
	{
		Start = 0;
		End = m_NormalEffectEnd;
	}
	else if (Type == ABlueFlyProjectile::StaticClass())
	{
		Start = m_NormalEffectEnd;
		End = m_NormalEffectEnd + m_BlueFlyBulletArray;
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

				//LOG(TEXT("S : %d"), i);
				return m_CustomActorArray[i];
			}
			//else
				//LOG(TEXT("SF : %d"), i);

		}
		//else
			//LOG(TEXT("F : %d"), i);
	}

	return nullptr;
}