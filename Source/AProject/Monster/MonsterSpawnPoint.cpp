// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "NavigationSystem.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AccTime = 0.f;
	m_SpawnTime = 1.f;
	m_Monster = nullptr;

	IsActivate = false;
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	/*if (m_MonsterClass)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClass,
			GetActorLocation(), GetActorRotation(), param);

		Monster->SetSpawnPoint(this);

		Monster->AddPatrolPoint(GetActorLocation());

		for (auto& Point : m_PatrolPointArray)
		{
			Monster->AddPatrolPoint(Point->GetActorLocation());
		}
		m_Monster = Monster;
	}*/
}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActivate)
	{
		if (!m_Monster)
		{
			m_AccTime += DeltaTime;

			if (m_AccTime >= m_SpawnTime)
			{
				m_AccTime = 0.f;

				FActorSpawnParameters	param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				int random = FMath::RandRange(0, m_MonsterClassArray.Num() - 1);

				AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClassArray[random],
					GetActorLocation(), GetActorRotation(), param);
				Monster->SetIsSpawned(true);
				Monster->GetMonsterInfo().TraceDistance = 4000.f;
				m_Monster = Monster;
			}
		}
	}
}

