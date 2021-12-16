// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Loading.h"
#include "../UI/MainHUD.h"
#include "../AProjectGameInstance.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
#include "../Player/PlayerCharacter.h"
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

	if (GameInst)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		FPlayerInfo& SavePlayerInfo = GameInst->GetPlayerInfo();
		FPlayerInfo& PlayerInfo = Player->GetPlayerInfo();
		if (&PlayerInfo)
		{
			SavePlayerInfo.Name = PlayerInfo.Name;
			SavePlayerInfo.Attack = PlayerInfo.Attack;
			SavePlayerInfo.Armor = PlayerInfo.Armor;
			SavePlayerInfo.HP = PlayerInfo.HP;
			SavePlayerInfo.HPMax = PlayerInfo.HPMax;
			SavePlayerInfo.MP = PlayerInfo.MP;
			SavePlayerInfo.MPMax = PlayerInfo.MPMax;
			SavePlayerInfo.Level = PlayerInfo.Level;
			SavePlayerInfo.Exp = PlayerInfo.Exp;
			SavePlayerInfo.Gold = PlayerInfo.Gold;
			SavePlayerInfo.AttackDistance = PlayerInfo.AttackDistance;
			SavePlayerInfo.AttackAngle = PlayerInfo.AttackAngle;
			SavePlayerInfo.MoveSpeed = PlayerInfo.MoveSpeed;
			SavePlayerInfo.SkillTree = PlayerInfo.SkillTree;
			SavePlayerInfo.CriticalPercent = PlayerInfo.CriticalPercent;
			SavePlayerInfo.CriticalDamage = PlayerInfo.CriticalDamage;

		}


	}
	//UGameplayStatics::OpenLevel(this, *m_StreamingLevelName);


	AAProjectGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AAProjectGameModeBase>();

	if (GameMode)
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (MainHUD)
		{
			MainHUD->GetLoadingWidget()->SetVisibility(ESlateVisibility::Visible);
			MainHUD->GetLoadingWidget()->SetMapImg(m_StreamingLevelName);
			MainHUD->GetLoadingWidget()->SetMapNameText(m_StreamingLevelName);


			GetWorld()->GetTimerManager().SetTimer(m_MapLoadTimer, this, &ALevelTrigger::LoadMap, 0.5f, false, -1.f);
		}
	}

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

