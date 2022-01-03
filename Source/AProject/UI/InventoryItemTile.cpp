// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemTile.h"
#include "InventoryTileData.h"
void UInventoryItemTile::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_IconImage = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}

void UInventoryItemTile::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryItemTile::SetData(UObject* Data)
{
	UInventoryTileData* InvenData = Cast<UInventoryTileData>(Data);

	UTexture2D* IconTexture = InvenData->GetIconTexture();

	if (IconTexture)
		m_IconImage->SetBrushFromTexture(IconTexture);
}


