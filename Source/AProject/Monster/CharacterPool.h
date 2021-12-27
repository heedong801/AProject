// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Etc/CustomCharacter.h"
#include "Monster.h"
#include "CharacterPool.generated.h"

enum MONSTER{ Barghest, BlueFly, Centour, Golem, Omnik, Shoebill};
UCLASS()
class APROJECT_API UCharacterPool : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<ACustomCharacter*> m_CustomCharacterArray;
	UPROPERTY()
	TArray<TSubclassOf<AMonster>> m_MonsterArray;

	int32 m_CustomCharacterArrayMaxIdx;
	int32 m_MonsterNum;
	
	//int32 m_GolemNum;
	//int32 m_BlueFlyNum;
	//int32 m_OmnikNum;
	//int32 m_CentourNum;
	//int32 m_BarghestNum;
	//int32 m_ShoebillNum;

public:
	UCharacterPool();

	void MakePool();
	int GetSize();

	ACustomCharacter* Pop(FVector Pos, FRotator Rot, UClass* Type);

	//int32 GetGolemEndIdx() { return m_GolemNum; }
	//int32 GetBlueFlyEndIdx() { return m_BlueFlyNum; }
	//int32 GetOmnikEndIdx() { return m_OmnikNum; }
	//int32 GetCentourEndIdx() { return m_CentourNum; }
	//int32 GetBarghestEndIdx() { return m_BarghestNum; }
	//int32 GetShoebillEndIdx() { return m_ShoebillNum; }
};
