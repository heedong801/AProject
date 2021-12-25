// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerInfo.h"
#include "Monster/MonsterInfo.h"
#include "Engine/GameInstance.h"
#include "Effect/ParticlePool.h"
#include "Monster/MonsterPool.h"
#include "Quest/QuestInfo.h"
#include "Manager/LevelManager.h"
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

	UPROPERTY()
	UParticlePool* m_ParticlePool;

	UPROPERTY()
		UMonsterPool* m_MonsterPool;

	UPROPERTY()
		UDataTable* m_UIItemInfoTable;

	UPROPERTY()
		UDataTable* m_MapInfoTable;

	UPROPERTY()
		UDataTable* m_QuestInfoTable;

	TMap<FString, FQuestData>	m_QuestDataMap;

	FString 	m_MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FPlayerInfo	m_PlayerInfo;

	UPROPERTY()
	ULevelManager* m_LevelManager;
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
	FPlayerInfo& GetPlayerInfo() { return m_PlayerInfo; }

	void SetMonsterPool(UMonsterPool* pM);
	void SetParticlePool(UParticlePool* pP);
	UMonsterPool* GetMonsterPool();
	UParticlePool* GetParticlePool();

	const FMonsterInfo* FindMonsterInfo(const FString& Name);
	const FPlayerInfo* FindPlayerInfo(const FString& Name);

	//const FUIItemTableInfo* FindUIItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
	const FMapTableInfo* FindMapInfo(const FString& Name);
	ULevelManager* GetLevelManager() { return m_LevelManager; }
public:
	void SetMapName(const FString& MapName) { m_MapName = MapName; }
	const FString& GetMapName() { return m_MapName; }
};
