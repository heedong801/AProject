// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "InventoryTileData.h"
#include "../AProjectGameModeBase.h"
void UEquipmentWidget::NativeConstruct()
{
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("headband"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("head"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("eye"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("neck"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("face"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("shoulder"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("armor"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("chest"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("body"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("mainhand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("mainwrist"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("belt"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("offwrist"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("offhand")))); //13
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("righthand")))); 
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("trousers"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("lefthand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("rightring"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("feet"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("leftring"))));

}

void UEquipmentWidget::SetPart(UInventoryTileData* Item, EItemPart Part, UTexture2D* Icon)
{
	int32 Idx = -1;
	
	switch (Part)
	{
	case EItemPart::HEADBAND:
	case EItemPart::HEAD:
	case EItemPart::EYE:
	case EItemPart::NECK:
	case EItemPart::FACE:
	case EItemPart::SHOULDER:
	case EItemPart::ARMOR:
	case EItemPart::CHEST:
	case EItemPart::BODY:
	case EItemPart::MAINHAND:
	case EItemPart::MAINWRIST:
	case EItemPart::BELT:
	case EItemPart::OFFWRIST:
	case EItemPart::OFFHAND:
		Idx = static_cast<int>(EItemPart::BODY) - 1;
		break;
	case EItemPart::HAND:
	{
		if (m_EquipmentImgArray[14]->GetVisibility() == ESlateVisibility::Collapsed)
			Idx = 14;
		else
			Idx = 16;
	}
		break;
	case EItemPart::TROUSERS:
		Idx = 15;
		break;
	case EItemPart::RING: 
	{
		if (m_EquipmentImgArray[17]->GetVisibility() == ESlateVisibility::Collapsed)
			Idx = 17;
		else
			Idx = 19;
	}
		break;
	case EItemPart::FEET:
		Idx = 18;
		break;
	}

	m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
	m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);

	m_EquipmentItemArray[Idx] = Item;
}

void UEquipmentWidget::UnsetPart(UInventoryTileData* Item)
{
	for (int32 i = 0; i < m_EquipmentItemArray.Num(); ++i)
	{
		if (m_EquipmentItemArray[i] == Item)
		{
			m_EquipmentImgArray[i]->SetVisibility(ESlateVisibility::Collapsed);
			

			AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
			if (IsValid(GameMode))
			{
				UMainHUD* MainHUD = GameMode->GetMainHUD();

				if (IsValid(MainHUD))
				{
					UInventoryTile* InventoryTile = MainHUD->GetInventory();

					if (IsValid(InventoryTile))
					{
						InventoryTile->GetEquipTile()->AddItem(Item);
					}
				}
			}
			return;
		}
	}
}