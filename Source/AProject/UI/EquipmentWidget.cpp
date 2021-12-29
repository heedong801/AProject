// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

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
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("offhand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("righthand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("trousers"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("lefthand"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("rightring"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("feet"))));
	m_EquipmentImgArray.Add(Cast<UImage>(GetWidgetFromName(TEXT("leftring"))));

}

void UEquipmentWidget::SetPart(int32 Idx, UTexture2D* Icon)
{
	m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
	m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);
}