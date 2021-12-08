// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerInfo.h"
#include "Monster/MonsterInfo.h"
#include "Engine/GameInstance.h"
#include "Effect/ParticlePool.h"
#include "Quest/QuestInfo.h"
#include "AProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UAProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UAProjectGameInstance();
	~UAProjectGameInstance();


private:
	UPROPERTY()
		UDataTable* m_MonsterInfoTable;

	UPROPERTY()
		UDataTable* m_PlayerInfoTable;

	UParticlePool* m_ParticlePool;

	UPROPERTY()
		UDataTable* m_UIItemInfoTable;

	UPROPERTY()
		UDataTable* m_MapInfoTable;

	UPROPERTY()
		UDataTable* m_QuestInfoTable;

	TMap<FString, FQuestData>	m_QuestDataMap;

	FString 	m_MapName;
public:
	const TMap<FString, FQuestData>& GetQuestData()
	{
		return m_QuestDataMap;
	}

	const FQuestData* FindQuestData(const FString& Name)
	{
		return m_QuestDataMap.Find(Name);
	}

	TMap<FString, FQuestData>* GetMap()
	{
		return &m_QuestDataMap;
	}
	virtual void Init();
	virtual void StartGameInstance();

	//bool GetParticlePoolIsSet();
	void SetParticlePool(UParticlePool* pP);
	int GetPoolSize();
	UParticlePool* GetParticlePool() { return m_ParticlePool; }
	const FMonsterInfo* FindMonsterInfo(const FString& Name);
	const FPlayerInfo* FindPlayerInfo(const FString& Name);

	//const FUIItemTableInfo* FindUIItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
	const FMapTableInfo* FindMapInfo(const FString& Name);


public:
	void SetMapName(const FString& MapName) { m_MapName = MapName; }
	const FString& GetMapName() { return m_MapName; }
};
