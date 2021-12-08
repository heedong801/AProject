// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestDescWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"

#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

UCLASS()
class APROJECT_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UListView* m_QuestList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UQuestDescWidget* m_QuestDesc;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UImage* m_MapImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_MapNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBorder* m_ImgBackBorder;

	FQuestData* m_CurrentRenderQuest;

	TArray<FQuestData>	m_QuestArray;

	class UQuestListItemData* m_PrevSelect;

	TArray<FQuestData*> m_QuestListArray[(uint8)EQuestType::Max];

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void SetImg(UImage* Img)
	{
		//m_MapImg->SetBrushFromTexture();
	}
public:
	UFUNCTION()
		void QuestClick(UObject* Data);

	UFUNCTION()
		void QuestSelect(UObject* Data);
	UFUNCTION()
		void QuestMouseOn(UObject* Data, bool IsHovered);

public:
	void QuestCheck(EQuestType Type, const FString& Name);
	void QuestSet();

	void ShowQuestSet(bool bShowFlag, const FString& MapName);
};
