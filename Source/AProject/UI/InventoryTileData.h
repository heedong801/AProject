// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryTileData.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UInventoryTileData : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTexture2D* m_IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemTier	m_Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EItemType	m_Type;
public:
	void SetIconTexture(UTexture2D* IconTex)
	{
		m_IconTexture = IconTex;
	}

	void SetName(const FString& NameText)
	{
		m_NameText = NameText;
	}

	UTexture2D* GetIconTexture()
	{
		return m_IconTexture;
	}

	FString GetName()
	{
		return m_NameText;
	}

	EItemTier GetTier()
	{
		return m_Tier;
	}

	void SetTier(EItemTier Tier)
	{
		m_Tier = Tier;
	}

	EItemType GetType()
	{
		return m_Type;
	}

	void SetType(EItemType Type)
	{
		m_Type = Type;
	}
};