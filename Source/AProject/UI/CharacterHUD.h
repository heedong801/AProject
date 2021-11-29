// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_LevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar* m_HPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar* m_MPBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar* m_EXPBar;

	//FNameDelegate	m_NameDelegate;

public:
	void SetHPPercent(float Percent)
	{
		m_HPBar->SetPercent(Percent);
	}

	void SetMPPercent(float Percent)
	{
		m_MPBar->SetPercent(Percent);
	}
	void SetEXPPercent(float Percent)
	{
		m_EXPBar->SetPercent(Percent);
	}
	void SetLevelText(int32 Level)
	{
		m_LevelText->SetText(FText::FromString(FString::FromInt(Level)));
	}

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};