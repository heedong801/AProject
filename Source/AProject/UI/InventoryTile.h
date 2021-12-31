// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"

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
		UTileView* m_InventoryTile;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UItemDescWidget* m_ItemDescWidget;*/
	bool	m_MouseHovered;
	int32	m_ItemCount;
public:
	UFUNCTION()
		void ItemClick(UObject* Data);

	UFUNCTION()
		void ItemScroll(UObject* Data, UUserWidget* Widget);

	UFUNCTION()
		void ItemHovered(UObject* Data, bool Hovered);

public:
	//void AddItem(const FUIItemTableInfo* ItemInfo);
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTine);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

};
