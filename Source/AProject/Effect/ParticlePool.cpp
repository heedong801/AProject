// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlePool.h"
#include "../DebugClass.h"
UParticlePool::UParticlePool()
	: m_NormalEffectArrayMaxIdx(20)
{
	
}

UParticlePool::~UParticlePool()
{
	/*LOG(TEXT("%d"), m_NormalEffectArray.Num());
	m_NormalEffectArray.RemoveAll([](NormalEffect* e) {return true; });
	LOG(TEXT("%d"), m_NormalEffectArray.Num());*/

}

void UParticlePool::MakePool()
{
	for (int32 i = 0; i < m_NormalEffectArrayMaxIdx; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			FVector::ZeroVector, FRotator::ZeroRotator, param);

		m_NormalEffectArray.Add(Effect);
	}
}


int UParticlePool::GetSize()
{
	return m_NormalEffectArray.Num(); 
}

ANormalEffect* UParticlePool::Pop(FVector Pos, FRotator Rot)
{
	for (int i = 0; i < m_NormalEffectArray.Num(); ++i)
	{
		if (m_NormalEffectArray[i]->GetActive() == false)
		{
			m_NormalEffectArray[i]->SetActive(true);
			m_NormalEffectArray[i]->SetActorLocation(Pos);
			m_NormalEffectArray[i]->SetActorRotation(Rot);
			return m_NormalEffectArray[i];
		}
	}

	return nullptr;
}