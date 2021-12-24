// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_CharacterHUD = Cast<UCharacterHUD>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
	m_Loading = Cast<ULoading>(GetWidgetFromName(TEXT("UI_Loading")));
	m_QuestWidget = Cast<UQuestWidget>(GetWidgetFromName(TEXT("UI_Quest")));
	m_DungeonSelect = Cast<UDungeonSelect>(GetWidgetFromName(TEXT("UI_DungeonSelect")));


	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
	FString MapName = GameInst->GetMapName();

	if (IsValid(m_Loading) && MapName.IsEmpty() == false)
	{
		//LOG(TEXT("B"));
		m_Loading->SetMapNameText(MapName);
		m_Loading->SetMapImg(MapName);
	}
}

void UMainHUD::QuitAllWidget()
{
	if(IsValid(m_QuestWidget))
		m_QuestWidget->SetVisibility(ESlateVisibility::Collapsed);
	if (IsValid(m_DungeonSelect))
		m_DungeonSelect->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainHUD::QuitAllWidgetAnim()
{
	PlayAnimation(m_FadeAnim);
}