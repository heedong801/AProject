// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/MainHUD.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
void ULevelManager::OpenNextLevel()
{
	UGameplayStatics::OpenLevel(this, *m_NextMapName);
}
void ULevelManager::OpenTownLevel()
{
	UGameplayStatics::OpenLevel(this, *m_TownMapName);

}

void ULevelManager::OpenDelayLevel()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();
		if (IsValid(MainHUD))
		{
			MainHUD->QuitAllWidgetAnim();
		}
	}
	GetWorld()->GetTimerManager().SetTimer(m_LevelOpenTimerHandle, this, &ULevelManager::OpenNextLevel, 3.1f, false, -1.f);
}