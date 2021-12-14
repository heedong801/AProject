// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUI.h"
#include "../DebugClass.h"
#include "Kismet/GameplayStatics.h"
void UDamageUI::NativeConstruct()
{
	Super::NativeConstruct();

	
	m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));	

	//SetPositionInViewport(m_Location);
	
	m_DamageText->SetText(FText::FromString(FString::FromInt(m_Damage)));

	PlayAnimation(m_FadeAnim);
}

void UDamageUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D ScreenLoc;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), m_Location, ScreenLoc);
	ScreenLoc += FVector2D(-50.f, -100.f);
	SetPositionInViewport(ScreenLoc);
}

void UDamageUI::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);
	
	SetActive(false);
}


void UDamageUI::SetActive(bool bOnActive)
{
	m_Active = bOnActive;
	if (bOnActive)
	{
		FVector2D ScreenLoc;
		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), m_Location, ScreenLoc);
		ScreenLoc += FVector2D(-50.f, -100.f);
		SetPositionInViewport(ScreenLoc);
		m_DamageText->SetText(FText::FromString(FString::FromInt(m_Damage)));
		PlayAnimation(m_FadeAnim);
	}
	else
	{
		RemoveFromParent();
	}
}

bool UDamageUI::GetActive() 
{
	return m_Active;
}