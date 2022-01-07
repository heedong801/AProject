// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerInfo.h"
#include "Monster/MonsterInfo.h"
#include "Engine/GameInstance.h"
#include "Quest/QuestInfo.h"
#include "UI/ItemInfo.h"
#include "Manager/LevelManager.h"
#include "Components/TileView.h"
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
		UDataTable* m_UIItemInfoTable;

	UPROPERTY()
		UDataTable* m_MapInfoTable;

	UPROPERTY()
		UDataTable* m_QuestInfoTable;

	TMap<FString, FQuestData>	m_QuestDataMap;

	FString 	m_MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FPlayerInfo	m_PlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEquipmentWidget* m_Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UObject*> m_EquipItemList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UObject*> m_QuestItemList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UObject*> m_ConsumItemList;

	UPROPERTY()
	ULevelManager* m_LevelManager;
public:
	void LoadData();
	void SaveData();

	void SetEquipmentWidget(class UEquipmentWidget* EquipmentWidget)	{		m_Equipment = EquipmentWidget;	}
	class UEquipmentWidget* GetEquipmentWidget()	{		return m_Equipment;	}

	//void SetInventoryTile(class UInventoryTile* InventoryUI);
	//TArray<UObject*>& GetEquipItemList() { return m_EquipItemList; }
	//TArray<UObject*>& GetQuestItemList() { return m_QuestItemList; }
	//TArray<UObject*>& GetConsumItemList() { return m_ConsumItemList; }

	const TMap<FString, FQuestData>& GetQuestData()	{		return m_QuestDataMap;	}
	const FQuestData* FindQuestData(const FString& Name)	{		return m_QuestDataMap.Find(Name);	}

	TMap<FString, FQuestData>* GetMap()	{		return &m_QuestDataMap;	}
	virtual void Init();
	virtual void StartGameInstance();
	FPlayerInfo& GetPlayerInfo() { return m_PlayerInfo; }

	const FMonsterInfo* FindMonsterInfo(const FString& Name);
	const FPlayerInfo* FindPlayerInfo(const FString& Name);
	const FUIItemTableInfo* FindUIItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
	const FMapTableInfo* FindMapInfo(const FString& Name);
	ULevelManager* GetLevelManager() { return m_LevelManager; }
public:
	void SetMapName(const FString& MapName) { m_MapName = MapName; }
	const FString& GetMapName() { return m_MapName; }
};
