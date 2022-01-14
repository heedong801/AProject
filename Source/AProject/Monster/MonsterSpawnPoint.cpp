// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "NavigationSystem.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_AccTime = 0.f;
	m_SpawnTime = 5.f;
	m_Monster = nullptr;

	IsActivate = false;
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
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
				
				AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

				UClass* Type = m_MonsterClassArray[random];

				AMonster* Monster = Cast<AMonster>(GameMode->GetCharacterPool()->Pop(GetActorLocation(), GetActorRotation(), m_MonsterClassArray[random]));
				
				if (Monster)
				{
					Monster->SetIsSpawned(true);
					Monster->SetSpawnPoint(this);
					//Monster->GetMonsterInfo().TraceDistance = 4000.f;
					m_Monster = Monster;
				}

				UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
				Monster->GetPatrolArray().RemoveAll([](FVector v) {return true; });
				//LOG(TEXT("%d"), Monster->GetPatrolArray().Num());
				while (Monster->GetPatrolArray().Num() < 4)
				{
					//LOG(TEXT("B"));
					FNavLocation NextPatrol;
					if (NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 500.0f, NextPatrol))
					{
						//LOG(TEXT("%f %f %f"), NextPatrol.Location.X, NextPatrol.Location.Y, NextPatrol.Location.Z);
						Monster->GetPatrolArray().Add(NextPatrol);
					}

					//LOG(TEXT("%f %f %f"), ranVec.X, ranVec.Y, ranVec.Z);
				}
			}
		}
	}
}

