// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonSelect.h"
#include "../AProjectGameInstance.h"
void UDungeonSelect::NativeConstruct()
{
	Super::NativeConstruct();

	//Button
	m_RuinButton = Cast<UButton>(GetWidgetFromName("RuinButton"));
	m_CaveButton = Cast<UButton>(GetWidgetFromName("CaveButton"));

	//Panel
	m_SelectSubPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("SelectSubPanel")));
	m_DescSubPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("DescSubPannel")));


	m_RuinButton->OnClicked.AddDynamic(this, &UDungeonSelect::RuinClick);
	m_CaveButton->OnClicked.AddDynamic(this, &UDungeonSelect::CaveClick);
}

void UDungeonSelect::RuinClick()
{
	GetOwningPlayerCameraManager()->StartCameraFade(0.0f, 1.f, 3.f, FLinearColor(0.f, 0.f, 0.f), true, true);

	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		GameInst->GetLevelManager()->SetNextMapName(TEXT("ExampleMap"));
		GameInst->GetLevelManager()->OpenDelayLevel();
	}

}
void UDungeonSelect::CaveClick()
{
	GetOwningPlayerCameraManager()->StartCameraFade(0.0f, 1.f, 3.f, FLinearColor(0.f, 0.f, 0.f), true, true);

	/*UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		GameInst->GetLevelManager()->SetNextMapName(TEXT("MountHuaguo"));
		GameInst->GetLevelManager()->OpenDelayLevel();
	}*/
}

