// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Loading.h"
#include "../UI/MainHUD.h"
#include "../AProjectGameModeBase.h"

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

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	
	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();
		
		if (IsValid(MainHUD))
		{
			ULoading* LoadingUI = MainHUD->GetLoadingWidget();
			

			if (IsValid(LoadingUI))
			{
				LoadingUI->SetMapNameText(m_StreamingLevelName);
				LoadingUI->SetLoadingUI();
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(m_MapLoadTimer, this, &ALevelTrigger::LoadMap, 0.1f, false, 0.5f);

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

