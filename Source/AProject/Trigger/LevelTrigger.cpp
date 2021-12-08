// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Loading.h"
#include "../UI/MainHUD.h"
#include "../AProjectGameInstance.h"
#include "../DebugClass.h"

ALevelTrigger::ALevelTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALevelTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ALevelTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &ALevelTrigger::TriggerEnd);
}

// Called every frame
void ALevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelTrigger::TriggerBegin()
{
	if (m_StreamingLevelName.Len() == 0)
		return;

	/*FLatentActionInfo	Info;

	UGameplayStatics::LoadStreamLevel(GetWorld(), *m_StreamingLevelName,
		true, false, Info);*/
	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	GameInst->SetMapName(m_StreamingLevelName);
	GetWorld()->GetTimerManager().SetTimer(m_MapLoadTimer, this, &ALevelTrigger::LoadMap, 1.f, false, 0.5f);

	//FLatentActionInfo	Info;

	/*UGameplayStatics::LoadStreamLevel(GetWorld(), *m_StreamingLevelName,
		true, false, Info);*/

}

void ALevelTrigger::TriggerEnd()
{
	//if (m_StreamingLevelName.Len() == 0)
	//	return;

	//FLatentActionInfo	Info;

	//UGameplayStatics::UnloadStreamLevel(GetWorld(), *m_StreamingLevelName,
	//	Info, false);
}

void ALevelTrigger::LoadMap()
{
	UGameplayStatics::OpenLevel(this, *m_StreamingLevelName);
}

