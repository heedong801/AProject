// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHUD.h"
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

public:
	UCharacterHUD* GetCharacterHUD()
	{
		return m_CharacterHUD;
	}

protected:
	virtual void NativeConstruct();

};
