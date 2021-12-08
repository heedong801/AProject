// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestInfo.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Collection,
	Hunt,
	Communication,
	Defense,
	Max
};

USTRUCT(BlueprintType)
struct FQuestInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EQuestType	Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	DestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32	Count;
};

UENUM(BlueprintType)
enum class EQuestCompensationType : uint8
{
	Gold,
	Item,
	Exp
};

USTRUCT(BlueprintType)
struct FQuestCompensationInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EQuestCompensationType	Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	Compensation;
};

USTRUCT(BlueprintType)
struct FQuestTableInfo :
	public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString	QuestDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FQuestInfo>	InfoArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FQuestCompensationInfo>	CompensationArray;
};

USTRUCT(BlueprintType)
struct FMapTableInfo :
	public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> MapTexture;
};

struct FQuestDataInfo
{
	EQuestType	Type;
	FString	DestName;
	int32	Count;
	int32	MaxCount;
	bool	Complete;
};

struct FQuestData
{
	FString	Name;
	FString	QuestDesc;
	TArray<FQuestDataInfo>	CompleteArray;
	TArray<FQuestCompensationInfo>	CompensationArray;
	bool	Complete;
};