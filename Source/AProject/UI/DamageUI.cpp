// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUI.h"
#include "../DebugClass.h"
#include "Kismet/GameplayStatics.h"
void UDamageUI::NativeConstruct()
{
	Super::NativeConstruct();

	
	m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));	

	//SetPositionInViewport(m_Location);
	
	if (m_Damage != 0.f)
		m_DamageText->SetText(FText::FromString(FString::FromInt(m_Damage)));
	else
		m_DamageText->SetText(FText::FromString(FString("MISS")));


	if( m_Critical == false)
		PlayAnimation(m_FadeAnim);
	else
		PlayAnimation(m_CriticalFadeAnim);

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
		if (m_Damage != 0.f)
			m_DamageText->SetText(FText::FromString(FString::FromInt(m_Damage)));
		else
			m_DamageText->SetText(FText::FromString(FString("MISS")));
		if (m_Critical == false)
			PlayAnimation(m_FadeAnim);
		else
			PlayAnimation(m_CriticalFadeAnim);
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