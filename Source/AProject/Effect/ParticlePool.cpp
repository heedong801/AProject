// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlePool.h"
#include "../DebugClass.h"
UParticlePool::UParticlePool()
	: m_CustomActorArrayMaxIdx(200)
{
	//LOG(TEXT("N : %d"), m_CustomActorArray.Num());
	//LOG(TEXT("M : %d"), m_CustomActorArrayMaxIdx);

}

UParticlePool::~UParticlePool()
{
	/*LOG(TEXT("%d"), m_CustomActorArray.Num());
	m_CustomActorArray.RemoveAll([](NormalEffect* e) {return true; });
	LOG(TEXT("%d"), m_CustomActorArray.Num());*/

}

void UParticlePool::MakePool()
{
	for (int32 i = 0; i < m_CustomActorArrayMaxIdx; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		m_CustomActorArray.Add(Effect);
	}

	//LOG(TEXT("MN : %d"), m_CustomActorArray.Num());
	//LOG(TEXT("MM : %d"), m_CustomActorArrayMaxIdx);
}


int UParticlePool::GetSize()
{
	return m_CustomActorArray.Num(); 
}

ACustomActor* UParticlePool::Pop(FVector Pos, FRotator Rot)
{
	LOG(TEXT("POP"));

	for (int32 i = 0; i < m_CustomActorArray.Num(); ++i)
	{
		if (m_CustomActorArray[i] != nullptr)
		{
			if (m_CustomActorArray[i]->GetActive() == false)
			{
				m_CustomActorArray[i]->SetActive(true);
				m_CustomActorArray[i]->SetActorLocation(Pos);
				m_CustomActorArray[i]->SetActorRotation(Rot);

				//LOG(TEXT("%d"), i);
				return m_CustomActorArray[i];
			}
		}
		else
			LOG(TEXT("%d"), i);
	}

	return nullptr;
}