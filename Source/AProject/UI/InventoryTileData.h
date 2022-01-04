// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
		int32	m_Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32	m_Tier;
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

	int32 GetIndex()
	{
		return m_Index;
	}

	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}

	int32 GetTier()
	{
		return m_Tier;
	}

	void SetTier(int32 Tier)
	{
		m_Tier = Tier;
	}
};