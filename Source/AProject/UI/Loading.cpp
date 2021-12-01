// Fill out your copyright notice in the Description page of Project Settings.


#include "Loading.h"
#include "../DebugClass.h"
void ULoading::NativeConstruct()
{
	Super::NativeConstruct();

	m_LoadingImg = Cast<UImage>(GetWidgetFromName(TEXT("LoadingImg")));
	m_MapNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MapNameText")));

	GetWorld()->GetTimerManager().SetTimer(m_LoadingTimer, this, &ULoading::UnSetLoadngUI, 0.1f, false, 3.f);
}

void ULoading::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULoading::SetLoadingUI()
{
	//SetVisibility(ESlateVisibility::Visible);

	//GetWorld()->GetTimerManager().SetTimer(m_LoadingTimer, this, &ULoading::UnSetLoadngUI, 0.1f, false, 5.f);
}

void ULoading::UnSetLoadngUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}