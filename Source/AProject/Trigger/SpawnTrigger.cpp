// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"
#include "../Monster/MonsterSpawnPoint.h"
#include "../DebugClass.h"
ASpawnTrigger::ASpawnTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	m_TriggerBeginDelegate.AddDynamic(this, &ASpawnTrigger::TriggerBegin);
}

// Called every frame
void ASpawnTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASpawnTrigger::TriggerBegin()
{
	LOG(TEXT("HI"));
	for (auto& Point : m_SpawnPointArray)
	{
		Point->SetActive(true);
	}
}	
