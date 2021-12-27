// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPool.h"
#include "../DebugClass.h"
#include "../Monster/Barghest.h"
#include "../Monster/BlueFly.h"
#include "../Monster/Centour.h"
#include "../Monster/Golem.h"
#include "../Monster/Omnik.h"
#include "../Monster/Shoebill.h"

UCharacterPool::UCharacterPool()
{
	//m_GolemNum = 5;
	//m_BlueFlyNum = 5;
	//m_OmnikNum = 5;
	//m_CentourNum = 5;
	//m_BarghestNum = 5;
	//m_ShoebillNum = 5;
	static ConstructorHelpers::FClassFinder<AMonster> BarghestClass(TEXT("Blueprint'/Game/Monster/Barghest/BP_Barhest.BP_Barhest_C'"));
	if (BarghestClass.Succeeded())
		m_MonsterArray.Add(BarghestClass.Class);

	static ConstructorHelpers::FClassFinder<AMonster> BlueFlyClass(TEXT("Blueprint'/Game/Monster/BlueFly/BP_BlueFly.BP_BlueFly_C'"));
	if (BlueFlyClass.Succeeded())
		m_MonsterArray.Add(BlueFlyClass.Class);

	static ConstructorHelpers::FClassFinder<AMonster> CentourClass(TEXT("Blueprint'/Game/Monster/Centour/BP_Centour.BP_Centour_C'"));
	if (CentourClass.Succeeded())
		m_MonsterArray.Add(CentourClass.Class);

	static ConstructorHelpers::FClassFinder<AMonster> GolemClass(TEXT("Blueprint'/Game/Monster/Golem/BP_Golem.BP_Golem_C'"));
	if (GolemClass.Succeeded())
		m_MonsterArray.Add(GolemClass.Class);

	static ConstructorHelpers::FClassFinder<AMonster> OmnikClass(TEXT("Blueprint'/Game/Monster/Omnik/BP_Omnik.BP_Omnik_C'"));
	if (OmnikClass.Succeeded())
		m_MonsterArray.Add(OmnikClass.Class);

	static ConstructorHelpers::FClassFinder<AMonster> ShoebillClass(TEXT("Blueprint'/Game/Monster/Shoebill/BP_Shoebill.BP_Shoebill_C'"));
	if (ShoebillClass.Succeeded())
		m_MonsterArray.Add(ShoebillClass.Class);
	m_MonsterNum = 20;
	//m_CustomCharacterArrayMaxIdx = m_GolemNum + m_BlueFlyNum + m_OmnikNum + m_CentourNum + m_BarghestNum + m_ShoebillNum;
	m_CustomCharacterArrayMaxIdx = m_MonsterNum * 6;
}

void UCharacterPool::MakePool()
{
	ACustomCharacter* Character = nullptr;

	for (int32 i = 0; i < m_CustomCharacterArrayMaxIdx; ++i)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (i < 20 )
			Character = GetWorld()->SpawnActor<AGolem>(m_MonsterArray[MONSTER::Golem], FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 40)
			Character = GetWorld()->SpawnActor<AShoebill>(m_MonsterArray[MONSTER::Shoebill], FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 60)
			Character = GetWorld()->SpawnActor<AOmnik>(m_MonsterArray[MONSTER::Omnik], FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 80)
			Character = GetWorld()->SpawnActor<ACentour>(m_MonsterArray[MONSTER::Centour], FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < 100)
			Character = GetWorld()->SpawnActor<ABarghest>(m_MonsterArray[MONSTER::Barghest], FVector::ZeroVector, FRotator::ZeroRotator, param);
		else if (i < m_CustomCharacterArrayMaxIdx)
			Character = GetWorld()->SpawnActor<ABlueFly>(m_MonsterArray[MONSTER::BlueFly], FVector::ZeroVector, FRotator::ZeroRotator, param);

		if (Character)
		{
			Character->SetActive(false);
			m_CustomCharacterArray.Add(Character);
		}
	}
	//LOG(TEXT("Size : %d"), m_CustomCharacterArray.Num());
}


int UCharacterPool::GetSize()
{
	return m_CustomCharacterArray.Num();
}

ACustomCharacter* UCharacterPool::Pop(FVector Pos, FRotator Rot, UClass* Type)
{
	//LOG(TEXT("%d"), m_CustomCharacterArray.Num());
	if (this != nullptr && IsValid(this) )
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
			if (m_CustomCharacterArray[i] != nullptr && IsValid(m_CustomCharacterArray[i]))
			{
				if (m_CustomCharacterArray[i]->GetActive() == false)
				{
					m_CustomCharacterArray[i]->SetActive(true);
					m_CustomCharacterArray[i]->SetActorLocation(Pos);
					m_CustomCharacterArray[i]->SetActorRotation(Rot);
					LOG(TEXT("%d"), i);
					return m_CustomCharacterArray[i];
				}
			}

		}

		return nullptr;
	}
	return nullptr;
}
