// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonUITrigger.h"
#include "../Player/PlayerCharacter.h"
#include "../AProjectGameModeBase.h"
ADungeonUITrigger::ADungeonUITrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	m_Trigger->SetCollisionProfileName(TEXT("NPC"));
}

void ADungeonUITrigger::TriggerBegin()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
		Player->SetInDungeonTrigger(true);
}

void ADungeonUITrigger::TriggerEnd()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
		Player->SetInDungeonTrigger(false);
}

void ADungeonUITrigger::Interaction()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UDungeonSelect* DungeonSelect = MainHUD->GetDungeonSelect();
			
			if (IsValid(DungeonSelect))
			{
				if (DungeonSelect->GetVisibility() == ESlateVisibility::Collapsed)
				{
					DungeonSelect->SetVisibility(ESlateVisibility::Visible);

					APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

					if (Player)
						Player->CursorUISet(true);
				}
				else
				{
					DungeonSelect->SetVisibility(ESlateVisibility::Collapsed);
			
					APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

					if (Player)
						Player->CursorUISet(false);
				}
			}
		}

	}

}