// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTile.h"
//#include "../UEKR2GameInstance.h"
//#include "Components/CanvasPanelSlot.h"
//#include "InventoryTileData.h"
void UInventoryTile::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemCount = 0;

	m_InventoryTile = Cast<UTileView>(GetWidgetFromName("InventoryTile"));
//	m_ItemDescWidget = Cast<UItemDescWidget>(GetWidgetFromName("UI_ItemDesc"));

	m_InventoryTile->SetScrollbarVisibility(ESlateVisibility::Collapsed);


	/*FString ItemNameArray[3] =
	{
		TEXT("BF대검"),
		TEXT("블클"),
		TEXT("HP포션")
	};*/

	/*for (int32 i = 0; i < 100; ++i)
	{
		int32 Idx = FMath::RandRange(0, 2);

		const FUIItemTableInfo* Info = GameInst->FindUIItemInfo(ItemNameArray[Idx]);

		UInventoryItemDataTile* Data = NewObject<UInventoryItemDataTile>(this, UInventoryItemDataTile::StaticClass());


		Data->SetIconTexture(Info->IconTexture);
		Data->SetIndex(i);
		Data->SetName(Info->Name);
		m_InventoryTile->AddItem(Data);

		if (i >= 20)
		{
			UInventoryTileData* DataSlot = NewObject<UInventoryTileData>(this, UInventoryTileData::StaticClass());
			m_InventorySlot->AddItem(DataSlot);

			m_SlotArray.Add(Data);

		}
	}*/

	m_ItemCount = 100;
	m_MouseHovered = false;
	// 클릭했을때 동작할 함수를 등록한다.
	//m_InventoryTile->SetScrollOffset(10.f);

	m_InventoryTile->OnItemClicked().AddUObject(this, &UInventoryTile::ItemClick);
	//m_InventoryTile->OnItemScrolledIntoView(this, &UInventoryTile::ItemScroll);
	//m_InventoryTile->OnItemSelectionChanged()
	//m_InventoryTile->OnItemDoubleClicked()
	m_InventoryTile->OnItemIsHoveredChanged().AddUObject(this, &UInventoryTile::ItemHovered);
}


FReply UInventoryTile::NativeOnMouseMove(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	//if (m_MouseHovered)
	//{
	//	//FVector2D	S

	//	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_ItemDescWidget->Slot);

	//	if (PanelSlot)
	//	{
	//		FVector2D	WidgetPos = InMouseEvent.GetScreenSpacePosition();

	//		//USlateBlueprintLibrary::ScreenToWidgetLocal(this, InGeometry,
	//		//	InMouseEvent.GetScreenSpacePosition(), WidgetPos);

	//		// 마우스의 Screen좌표를 위젯의 Local 좌표로 변경한다.
	//		WidgetPos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry,
	//			WidgetPos);

	//		WidgetPos.X += 1.f;
	//		WidgetPos.Y += 1.f;

	//		PanelSlot->SetPosition(WidgetPos);

	//		PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("X : %.5f Y : %.5f"), WidgetPos.X, WidgetPos.Y));
	//	}
	//}

	return FReply::Handled();
}


void UInventoryTile::NativeTick(const FGeometry& MyGeometry, float InDeltaTine)
{
	Super::NativeTick(MyGeometry, InDeltaTine);
}

void UInventoryTile::ItemClick(UObject* Data)
{
	/*UInventoryItemDataTile* Item = Cast<UInventoryItemDataTile>(Data);

	if (Item)
	{
		m_InventoryTile->RemoveItem(Data);
		m_InventorySlot->RemoveItem(m_SlotArray[Item->GetIndex()]);

		if (m_SlotArray.Num() > 20)
			m_SlotArray.RemoveAt(Item->GetIndex());
	}*/
}


void UInventoryTile::ItemScroll(UObject* Data, UUserWidget* Widget)
{
}

void UInventoryTile::ItemHovered(UObject* Data, bool Hovered)
{
	m_MouseHovered = Hovered;

	/*if (Hovered)
	{
		m_ItemDescWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UInventoryItemDataTile* Item = Cast<UInventoryItemDataTile>(Data);


		if (Item)
		{
			m_ItemDescWidget->SetName(Item->GetName());
			m_ItemDescWidget->SetIconTexture(Item->GetIconTexture());
			PrintViewport(1.0f, FColor::Red, Item->GetName());
		}
	}
	else
		m_ItemDescWidget->SetVisibility(ESlateVisibility::Collapsed);*/

}


//void UInventoryTile::AddItem(const FUIItemTableInfo* ItemInfo)
//{
//	UInventoryItemDataTile* Data = NewObject<UInventoryItemDataTile>(this,
//		UInventoryItemDataTile::StaticClass());
//
//	Data->SetNameText(ItemInfo->Name);
//	Data->SetIconTexture(ItemInfo->IconTexture);
//	Data->SetIndex(m_InventoryTile->GetNumItems());
//
//	m_InventoryTile->AddItem(Data);
//}
