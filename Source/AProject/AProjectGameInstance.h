// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerInfo.h"
#include "Monster/MonsterInfo.h"
#include "Engine/GameInstance.h"
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

	/*UPROPERTY()
		UDataTable* m_UIItemInfoTable;

	UPROPERTY()
		UDataTable* m_QuestInfoTable;

	EPlayerJob m_SelectJob;

	TMap<FString, FQuestData>	m_QuestComplete;*/
public:
	/*const TMap<FString, FQuestData>& GetQuestData()
	{
		return m_QuestComplete;
	}

	const FQuestData* FindQuestData(const FString& Name)
	{
		return m_QuestComplete.Find(Name);
	}
	void SetSelectJob(EPlayerJob Job)
	{
		m_SelectJob = Job;
	}

	EPlayerJob GetSelectJob()	const
	{
		return m_SelectJob;
	}
	virtual void Init();*/

	const FMonsterInfo* FindMonsterInfo(const FString& Name);
	const FPlayerInfo* FindPlayerInfo(const FString& Name);
	//const FUIItemTableInfo* FindUIItemInfo(const FString& Name);
	//const FQuestTableInfo* FindQuestInfo(const FString& Name);

};
