// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/EngineTypes.h"
#include "Loading.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ULoading : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UImage* m_LoadingImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_MapNameText;

	FTimerHandle m_LoadingTimer;
public:
	//void SetImg(float Percent) { m_HPBar->SetPercent(Percent); }
	void SetMapNameText(const FString& Name) {		m_MapNameText->SetText(FText::FromString(Name));	}

	void SetLoadingUI();
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);



	UFUNCTION()
	void UnSetLoadngUI();

};

