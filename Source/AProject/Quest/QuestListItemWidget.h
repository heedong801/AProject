// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestListItemData.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Blueprint/UserWidget.h"
#include "QuestListItemWidget.generated.h"

/**
 *
 */
UCLASS()
class APROJECT_API UQuestListItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UImage* m_Selection;

	class UQuestListItemData* m_PrevMouseOnItem;

	bool m_Select;
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION(BlueprintCallable)
		void SetData(UObject* Data);

	void Select(bool Enable);
	void MouseOn(bool Enable);
};
