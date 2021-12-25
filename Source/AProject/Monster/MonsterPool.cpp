// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPool.h"
#include "../DebugClass.h"
#include "../Monster/Barghest.h"
#include "../Monster/BlueFly.h"
#include "../Monster/Centour.h"
#include "../Monster/Golem.h"
#include "../Monster/Omnik.h"
#include "../Monster/Shoebill.h"

UMonsterPool::UMonsterPool()
{
	//m_GolemNum = 5;
	//m_BlueFlyNum = 5;
	//m_OmnikNum = 5;
	//m_CentourNum = 5;
	//m_BarghestNum = 5;
	//m_ShoebillNum = 5;
	
	m_MonsterNum = 20;
	//m_CustomCharacterArrayMaxIdx = m_GolemNum + m_BlueFlyNum + m_OmnikNum + m_CentourNum + m_BarghestNum + m_ShoebillNum;
	m_CustomCharacterArrayMaxIdx = m_MonsterNum * 6;
}

void UMonsterPool::MakePool()
{
	ACustomCharacter* Character = nullptr;

	for (int32 i = 0; i < m_CustomCharacterArrayMaxIdx; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (i < 20 )
			Character = GetWorld()->SpawnActor<AGolem>(AGolem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 40)
			Character = GetWorld()->SpawnActor<AShoebill>(AShoebill::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 60)
			Character = GetWorld()->SpawnActor<AOmnik>(AOmnik::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 80)
			Character = GetWorld()->SpawnActor<ACentour>(ACentour::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 100)
			Character = GetWorld()->SpawnActor<ABarghest>(ABarghest::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < m_CustomCharacterArrayMaxIdx)
			Character = GetWorld()->SpawnActor<ABlueFly>(ABlueFly::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, param);

		if (Character)
		{
			Character->SetActive(false);
			m_CustomCharacterArray.Add(Character);
		}
	}
}


int UMonsterPool::GetSize()
{
	return m_CustomCharacterArray.Num();
}

ACustomCharacter* UMonsterPool::Pop(FVector Pos, FRotator Rot, UClass* Type)
{
	if (this != nullptr && IsValid(this))
	{
		//LOG(TEXT("POP"));
		int32 Start = 0, End = m_CustomCharacterArrayMaxIdx;

		//LOG(TEXT("%s"), *Type->GetSuperClass()->GetName());
		if (Type->GetSuperClass() == AGolem::StaticClass())
		{
			LOG(TEXT("A"));
			Start = 0;
			End = 20;
		}
		else if (Type->GetSuperClass() == AShoebill::StaticClass())
		{
			LOG(TEXT("B"));

			Start = 20;
			End = 40;
		}
		else if (Type->GetSuperClass() == AOmnik::StaticClass())
		{
			LOG(TEXT("C"));

			Start = 40;
			End = 60;
		}
		else if (Type->GetSuperClass() == ACentour::StaticClass())
		{
			LOG(TEXT("D"));

			Start = 60;
			End = 80;
		}
		else if (Type->GetSuperClass() == ABarghest::StaticClass())
		{
			LOG(TEXT("E"));

			Start = 80;
			End = 100;
		}
		else if (Type->GetSuperClass() == ABlueFly::StaticClass())
		{
			LOG(TEXT("F"));

			Start = 100;
			End = 120;
		}

		for (int32 i = Start; i < End; ++i)
		{
			if (m_CustomCharacterArray[i] != nullptr)
			{
				if (m_CustomCharacterArray[i]->GetActive() == false)
				{
					m_CustomCharacterArray[i]->SetActive(true);
					m_CustomCharacterArray[i]->SetActorLocation(Pos);
					m_CustomCharacterArray[i]->SetActorRotation(Rot);

					return m_CustomCharacterArray[i];
				}
			}

		}

		return nullptr;
	}
	return nullptr;
}
