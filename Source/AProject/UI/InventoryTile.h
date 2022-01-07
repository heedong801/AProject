// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "Components/Button.h"
#include "ItemInfo.h"
#include "InventoryTile.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UInventoryTile : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_EquipTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_QuestTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTileView* m_ConsumTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_EquipButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_ConsumableButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_QuestButton;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UItemDescWidget* m_ItemDescWidget;*/
	bool	m_MouseHovered;
	int32	m_ItemCount;


public:
	void LoadData(TArray<UObject*> EquipItemList, TArray<UObject*> ConsumeItemList, TArray<UObject*> QuestItemList);

	TArray<UObject*> GetEquipItemList() { return m_EquipTile->GetListItems(); }
	TArray<UObject*> GeQuestItemList() { return m_QuestTile->GetListItems(); }
	TArray<UObject*> GetConsumItemList() { return m_ConsumTile->GetListItems();}


	UFUNCTION()
		void ItemScroll(UObject* Data, UUserWidget* Widget);

	UFUNCTION()
		void ItemHovered(UObject* Data, bool Hovered);

	UFUNCTION()
	void QuestClick();

	UFUNCTION()
		void ConsumClick();

	UFUNCTION()
		void EquipClick();


	UFUNCTION()
		void ConsumItemClick(UObject* Data);

	UFUNCTION()
		void EquipItemClick(UObject* Data);
public:
	void AddItem(const FUIItemTableInfo* ItemInfo);
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTine);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

};
