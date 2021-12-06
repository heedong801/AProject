// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUD.h"
#include "Loading.h"
#include "../Quest/QuestWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCharacterHUD* m_CharacterHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ULoading* m_Loading;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UQuestWidget* m_QuestWidget;

public:
	UCharacterHUD* GetCharacterHUD()
	{
		return m_CharacterHUD;
	}
	ULoading* GetLoadingWidget()
	{
		return m_Loading;
	}
	UQuestWidget* GetQuestWidget()
	{
		return m_QuestWidget;
	}

protected:
	virtual void NativeConstruct();

};
