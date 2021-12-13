// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUI.h"
#include "../DebugClass.h"
void UDamageUI::NativeConstruct()
{
	Super::NativeConstruct();

	
	m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));	

	SetPositionInViewport(m_Location);
	
	m_DamageText->SetText(FText::FromString(FString::FromInt(m_Damage)));

	PlayAnimation(m_FadeAnim);
}

void UDamageUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	SetPositionInViewport(m_Location);
}

void UDamageUI::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);
	
	RemoveFromParent();
}
