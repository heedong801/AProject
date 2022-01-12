// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "InventoryTileData.h"
#include "../AProjectGameModeBase.h"
#include "../Player/PlayerCharacter.h"
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

	m_AttackText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackText")));
	m_ArmorText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorText")));
	m_MaxHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHPText")));
	m_MaxMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxMPText")));
	m_HPRecoveryText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPRecoveryText")));
	m_MPRecoveryText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPRecoveryText")));
	m_CriPerText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CriticalPerText")));
	m_CriDmgText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CriticalDmgText")));

	m_EquipmentItemArray.Init(nullptr, 19);

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		m_AttackText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().Attack)));
		m_ArmorText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().Armor)));
		m_MaxHPText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().HPMax)));
		m_MaxMPText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().MPMax)));
		m_HPRecoveryText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().HPRecovery)));
		m_MPRecoveryText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().MPRecovery)));
		m_CriPerText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().CriticalPercent)));
		m_CriDmgText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().CriticalDamage)));
	}
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
		Idx = static_cast<int>(Part) - 1;
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
	if (Idx != -1)
	{
		if (m_EquipmentImgArray[Idx]->GetVisibility() != ESlateVisibility::Visible)
		{
			m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
			m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);

			m_EquipmentItemArray[Idx] = Item;
		}
		else
		{
			UnsetPart(m_EquipmentItemArray[Idx]);

			m_EquipmentImgArray[Idx]->SetBrushFromTexture(Icon);
			m_EquipmentImgArray[Idx]->SetVisibility(ESlateVisibility::Visible);

			m_EquipmentItemArray[Idx] = Item;
		}
	}

	SetStat(Item, true);
	SetStatText();
}

void UEquipmentWidget::UnsetPart(UInventoryTileData* Item)
{
	for (int32 i = 0; i < m_EquipmentItemArray.Num(); ++i)
	{
		if (m_EquipmentItemArray[i] == Item)
		{
			m_EquipmentImgArray[i]->SetVisibility(ESlateVisibility::Collapsed);

			SetStat(Item, false);
			break;
		}
	}
	SetStatText();
	
}

void UEquipmentWidget::SetStatText()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		m_AttackText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().Attack)));
		m_ArmorText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().Armor)));
		m_MaxHPText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().HPMax)));
		m_MaxMPText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().MPMax)));
		m_HPRecoveryText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().HPRecovery)));
		m_MPRecoveryText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().MPRecovery)));
		m_CriPerText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().CriticalPercent)));
		m_CriDmgText->SetText(FText::FromString(FString::FromInt(Player->GetPlayerInfo().CriticalDamage)));
	}
}

void UEquipmentWidget::SetStat(UInventoryTileData* Item, bool bOnPlus)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		FPlayerInfo Info = Player->GetPlayerInfo();
		int Size = Item->GetOption().Num();
		if (bOnPlus)
		{
			for (int32 j = 0; j < Size; ++j)
			{
				EItemOption OptionType = Item->GetOption()[j].OptionType;
				float OptionValue = Item->GetOption()[j].Option;
				switch (OptionType)
				{
				case EItemOption::Attack:
					Info.Attack += OptionValue;
					break;
				case EItemOption::Armor:
					Info.Armor += OptionValue;
					break;
				case EItemOption::HPMax:
					Info.HPMax += OptionValue;
					break;
				case EItemOption::MPMax:
					Info.MPMax += OptionValue;
					break;
				case EItemOption::HP:
					Info.HP += OptionValue;
					break;
				case EItemOption::MP:
					Info.MP += OptionValue;
					break;
				case EItemOption::HPRecovery:
					Info.HPRecovery += OptionValue;
					break;
				case EItemOption::MPRecovery:
					Info.MPRecovery += OptionValue;
					break;
				case EItemOption::CriticalPercent:
					Info.CriticalPercent += OptionValue;
					break;
				case EItemOption::CriticalDamage:
					Info.CriticalDamage += OptionValue;
					break;
				}
			}
		}
		else
		{
			for (int32 j = 0; j < Size; ++j)
			{
				EItemOption OptionType = Item->GetOption()[j].OptionType;
				float OptionValue = Item->GetOption()[j].Option;
				switch (OptionType)
				{
				case EItemOption::Attack:
					Info.Attack -= OptionValue;
					break;
				case EItemOption::Armor:
					Info.Armor -= OptionValue;
					break;
				case EItemOption::HPMax:
					Info.HPMax -= OptionValue;
					break;
				case EItemOption::MPMax:
					Info.MPMax -= OptionValue;
					break;
				case EItemOption::HP:
					break;
				case EItemOption::MP:
					break;
				case EItemOption::HPRecovery:
					Info.HPRecovery -= OptionValue;
					break;
				case EItemOption::MPRecovery:
					Info.MPRecovery -= OptionValue;
					break;
				case EItemOption::CriticalPercent:
					Info.CriticalPercent -= OptionValue;
					break;
				case EItemOption::CriticalDamage:
					Info.CriticalDamage -= OptionValue;
					break;
				}
			}
		}
		Player->SetPlayerInfo(Info);
	}

}