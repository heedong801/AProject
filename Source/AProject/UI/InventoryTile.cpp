// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTile.h"
#include "InventoryTileData.h"
#include "../AProjectGameInstance.h"
//#include "InventoryTileData.h"
#include "../DebugClass.h"
#include "EquipmentWidget.h"
#include "../AProjectGameModeBase.h"
void UInventoryTile::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemCount = 0;

	m_EquipTile = Cast<UTileView>(GetWidgetFromName("EquipTile"));
	m_ConsumTile = Cast<UTileView>(GetWidgetFromName("ConsumeTile"));
	m_CurrentEquipTile = Cast<UTileView>(GetWidgetFromName("CurrentEquipTile"));

	m_EquipButton = Cast<UButton>(GetWidgetFromName("EquipButton"));
	m_ConsumableButton = Cast<UButton>(GetWidgetFromName("ConsumableButton"));
	m_CurrentEquipButton = Cast<UButton>(GetWidgetFromName("CurrentEquipButton"));

//	m_ItemDescWidget = Cast<UItemDescWidget>(GetWidgetFromName("UI_ItemDesc"));

	m_EquipButton->OnClicked.AddDynamic(this, &UInventoryTile::EquipClick);
	m_ConsumableButton->OnClicked.AddDynamic(this, &UInventoryTile::ConsumClick);
	m_CurrentEquipButton->OnClicked.AddDynamic(this, &UInventoryTile::CurrentEquipClick);


	m_ItemCount = 100;
	m_MouseHovered = false;
	// 클릭했을때 동작할 함수를 등록한다.
	//m_InventoryTile->SetScrollOffset(10.f);
	
	m_EquipTile->OnItemClicked().AddUObject(this, &UInventoryTile::EquipItemClick);
	m_ConsumTile->OnItemClicked().AddUObject(this, &UInventoryTile::ConsumItemClick);
	m_CurrentEquipTile->OnItemClicked().AddUObject(this, &UInventoryTile::CurrentEquipItemClick);

	//m_InventoryTile->OnItemScrolledIntoView(this, &UInventoryTile::ItemScroll);
	//m_InventoryTile->OnItemSelectionChanged()
	//m_InventoryTile->OnItemDoubleClicked()
	//m_InventoryTile->OnItemIsHoveredChanged().AddUObject(this, &UInventoryTile::ItemHovered);

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


void UInventoryTile::AddItem(const FUIItemTableInfo* ItemInfo)
{
	UInventoryTileData* Data = NewObject<UInventoryTileData>(this,
		UInventoryTileData::StaticClass());

	Data->SetName(ItemInfo->Name);
	Data->SetIconTexture(ItemInfo->IconTexture);
	//Data->SetIndex(m_InventoryTile->GetNumItems());
	Data->SetTier(ItemInfo->ItemTier);
	Data->SetType(ItemInfo->ItemType);
	Data->SetPart(ItemInfo->ItemPart);
	Data->SetOption(ItemInfo->OptionArray);


	if(ItemInfo->ItemType == EItemType::Equipment )
		m_EquipTile->AddItem(Data);
	else if(ItemInfo->ItemType == EItemType::Consumable)
		m_ConsumTile->AddItem(Data);


}


void UInventoryTile::EquipClick()
{
	m_EquipTile->SetVisibility(ESlateVisibility::Visible);
	m_ConsumTile->SetVisibility(ESlateVisibility::Collapsed);
	m_CurrentEquipTile->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryTile::ConsumClick()
{
	m_EquipTile->SetVisibility(ESlateVisibility::Collapsed);
	m_ConsumTile->SetVisibility(ESlateVisibility::Visible);
	m_CurrentEquipTile->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryTile::CurrentEquipClick()
{
	m_EquipTile->SetVisibility(ESlateVisibility::Collapsed);
	m_ConsumTile->SetVisibility(ESlateVisibility::Collapsed);
	m_CurrentEquipTile->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryTile::LoadData(TArray<UObject*> EquipItemList, TArray<UObject*> ConsumeItemList, TArray<UObject*> QuestItemList)
{
	m_EquipTile->SetListItems(EquipItemList);
	m_ConsumTile->SetListItems(ConsumeItemList);
	m_CurrentEquipTile->SetListItems(QuestItemList);
}

void UInventoryTile::ConsumItemClick(UObject* Data)
{
	UInventoryTileData* Item = Cast<UInventoryTileData>(Data);

	m_ConsumTile->RemoveItem(Data);

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UEquipmentWidget* Equipment = MainHUD->GetEquipment();
			if (IsValid(Equipment))
			{
				Equipment->SetPart(Item, Item->GetPart(), Item->GetIconTexture());
			}
		}
	}
}

void UInventoryTile::EquipItemClick(UObject* Data)
{
	UInventoryTileData* Item = Cast<UInventoryTileData>(Data);
	
	m_EquipTile->RemoveItem(Data);
	m_CurrentEquipTile->AddItem(Data);

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UEquipmentWidget* Equipment = MainHUD->GetEquipment();
			if (IsValid(Equipment))
			{
				int Idx = Equipment->PartToIdx(Item->GetPart());
				UInventoryTileData* ChangeItem = Equipment->AlreadyPartSet(Idx);
				if (ChangeItem != nullptr)
				{
					m_EquipTile->AddItem(ChangeItem);
					m_CurrentEquipTile->RemoveItem(ChangeItem);
				}
				Equipment->SetPart(Item, Item->GetPart(), Item->GetIconTexture());

			}
		}
	}

}

void UInventoryTile::CurrentEquipItemClick(UObject* Data)
{
	UInventoryTileData* Item = Cast<UInventoryTileData>(Data);
	LOG(TEXT("%s"), *Item->GetName());

	m_CurrentEquipTile->RemoveItem(Data);
	m_EquipTile->AddItem(Data);

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UEquipmentWidget* Equipment = MainHUD->GetEquipment();
			if (IsValid(Equipment))
			{
				Equipment->UnsetPart(Item);
			}
		}
	}
}
