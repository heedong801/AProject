// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_CharacterHUD = Cast<UCharacterHUD>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	m_Loading = Cast<ULoading>(GetWidgetFromName(TEXT("UI_Loading")));
	m_QuestWidget = Cast<UQuestWidget>(GetWidgetFromName(TEXT("UI_Quest")));
}

