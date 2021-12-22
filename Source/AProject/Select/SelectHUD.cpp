// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectHUD.h"
#include "SelectPlayer.h"

void USelectHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_WukongButton = Cast<UButton>(GetWidgetFromName("WukongButton"));
	m_NoneButton = Cast<UButton>(GetWidgetFromName("NoneButton"));
	m_WukongText = Cast<UTextBlock>(GetWidgetFromName("WukongText"));
	m_NoneText = Cast<UTextBlock>(GetWidgetFromName("NoneText"));
	m_WukongBorder = Cast<UBorder>(GetWidgetFromName(TEXT("WukongBorder")));
	m_NoneBorder = Cast<UBorder>(GetWidgetFromName(TEXT("NoneBorder")));
	m_MainBorder = Cast<UBorder>(GetWidgetFromName(TEXT("Back")));

	m_WukongDesc = Cast<UUserWidget>(GetWidgetFromName(TEXT("UI_WukongDesc")));

	m_WukongButton->OnClicked.AddDynamic(this, &USelectHUD::WukongClick);
	m_NoneButton->OnClicked.AddDynamic(this, &USelectHUD::NoneClick);
}


void USelectHUD::WukongClick()
{
	m_WukongDesc->SetVisibility(ESlateVisibility::Visible);
	m_NoneBorder->SetVisibility(ESlateVisibility::Collapsed);
	m_WukongBorder->SetVisibility(ESlateVisibility::Collapsed);
	m_WukongText->SetVisibility(ESlateVisibility::Collapsed);
	m_NoneText->SetVisibility(ESlateVisibility::Collapsed);
	m_MainBorder->SetVisibility(ESlateVisibility::Collapsed);

}
void USelectHUD::NoneClick()
{
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASelectPlayer* Monster = GetWorld()->SpawnActor<ASelectPlayer>(m_Pawn,
		FVector(-10.0f, 190.f, 140.f), FRotator::ZeroRotator, param);
}