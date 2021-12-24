// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "DungeonSelect.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UDungeonSelect : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCanvasPanel* m_SelectSubPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCanvasPanel* m_DescSubPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_RuinButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_CaveButton;
protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
		void RuinClick();
	UFUNCTION()
		void CaveClick();
};
