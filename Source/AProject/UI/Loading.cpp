// Fill out your copyright notice in the Description page of Project Settings.


#include "Loading.h"
#include "../DebugClass.h"
#include "../Quest/QuestInfo.h"
#include "../AProjectGameInstance.h"
#include "../Player/PlayerCharacter.h"
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

void ULoading::SetMapImg(const FString& MapName)
{
	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	const FMapTableInfo* Info = GameInst->FindMapInfo(MapName);

	if (Info)
	{
		int random = FMath::RandRange(0, Info->MapTexture.Num() - 1);
		//LOG(TEXT("%d"), random);
		UTexture2D* IconTexture = Info->MapTexture[random];

		if (IconTexture)
			m_LoadingImg->SetBrushFromTexture(IconTexture); 
	}
}

void ULoading::UnSetLoadngUI()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	///FInputModeUIOnly	Mode;
	FInputModeGameOnly Mode;
	//FInputModeGameAndUI	Mode;

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = false;

	SetVisibility(ESlateVisibility::Collapsed);
}