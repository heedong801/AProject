// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ItemInfo.h"
#include "EquipmentWidget.generated.h"

//enum class PART : uint8{ HEADBAND, HEAD, EYE, NECK, FACE, SHOULDER, ARMOR, CHEST, BODY, MAINHAND, MAINWRIST, BELT, OFFWRIST, OFFHAND,
//	RIGHTHAND,TROUSERS, LEFTHAND, RIGHTRING, FEET, LEFTRING};

UCLASS()
class APROJECT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UImage*> m_EquipmentImgArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class UInventoryTileData*> m_EquipmentItemArray;
protected:
	virtual void NativeConstruct();

public:
	void SetPart(UInventoryTileData* Item, EItemPart Part, UTexture2D* Icon);
	void UnsetPart(class UInventoryTileData* Item);
};
