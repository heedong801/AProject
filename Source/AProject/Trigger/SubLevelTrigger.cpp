// Fill out your copyright notice in the Description page of Project Settings.


#include "SubLevelTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Loading.h"
#include "../UI/MainHUD.h"
#include "../AProjectGameInstance.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
#include "../Player/PlayerCharacter.h"
ASubLevelTrigger::ASubLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASubLevelTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ASubLevelTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &ASubLevelTrigger::TriggerEnd);
}


void ASubLevelTrigger::TriggerBegin()
{
	FLatentActionInfo	Info;

	if (m_StreamingLevelName.Len() != 0)
		UGameplayStatics::LoadStreamLevel(GetWorld(), *m_StreamingLevelName,true, false, Info);

	
	if (m_ExceptStreamingLevelName.Len() != 0)
		UGameplayStatics::UnloadStreamLevel(GetWorld(), *m_ExceptStreamingLevelName,Info, false);


}

void ASubLevelTrigger::TriggerEnd()
{

}
