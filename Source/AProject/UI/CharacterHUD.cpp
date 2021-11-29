// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"
#include "../Player/PlayerCharacter.h"

void UCharacterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));	
	m_EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EXPBar")));

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		SetLevelText(Player->GetPlayerInfo().Level);
	}
}

void UCharacterHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


