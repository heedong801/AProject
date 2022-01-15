// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectGameInstance.h"
#include "DebugClass.h"
#include "UI/InventoryTile.h"
#include "AProjectGameModeBase.h"
UAProjectGameInstance::UAProjectGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTableAsset(TEXT("DataTable'/Game/Monster/DT_MonsterInfo.DT_MonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTableAsset(TEXT("DataTable'/Game/Player/DT_PlayerInfo.DT_PlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> QuestInfoTableAsset(TEXT("DataTable'/Game/Quest/DT_QuestInfo.DT_QuestInfo'"));
	if (QuestInfoTableAsset.Succeeded())
		m_QuestInfoTable = QuestInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> UIItemInfoTableAsset(TEXT("DataTable'/Game/UI/DT_ItemInfo.DT_ItemInfo'"));
	if (UIItemInfoTableAsset.Succeeded())
		m_UIItemInfoTable = UIItemInfoTableAsset.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> MapInfoTableAsset(TEXT("DataTable'/Game/Quest/DT_MapInfo.DT_MapInfo'"));
	if (MapInfoTableAsset.Succeeded())
		m_MapInfoTable = MapInfoTableAsset.Object;
}

UAProjectGameInstance::~UAProjectGameInstance()
{
	
}

void UAProjectGameInstance::Init()
{
	Super::Init();

	m_LevelManager = NewObject<ULevelManager>(this, ULevelManager::StaticClass(), TEXT("LevelManager"));
}

void UAProjectGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}


const FMonsterInfo* UAProjectGameInstance::FindMonsterInfo(const FString& Name)
{
	return m_MonsterInfoTable->FindRow<FMonsterInfo>(*Name, "");
}


const FPlayerInfo* UAProjectGameInstance::FindPlayerInfo(const FString& Name)
{
	return m_PlayerInfoTable->FindRow<FPlayerInfo>(*Name, "");
}

const FUIItemTableInfo* UAProjectGameInstance::FindUIItemInfo(const FString& Name)
{
	return m_UIItemInfoTable->FindRow<FUIItemTableInfo>(*Name, "");
}

const FQuestTableInfo* UAProjectGameInstance::FindQuestInfo(const FString& Name)
{
	return m_QuestInfoTable->FindRow<FQuestTableInfo>(*Name, "");
}

const FMapTableInfo* UAProjectGameInstance::FindMapInfo(const FString& Name)
{
	return m_MapInfoTable->FindRow<FMapTableInfo>(*Name, "");
}

void UAProjectGameInstance::LoadData()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UInventoryTile* InventoryTile = MainHUD->GetInventory();

			if (IsValid(InventoryTile))
				InventoryTile->LoadData(m_EquipItemList, m_ConsumItemList, m_CurrentEquipList);

			UEquipmentWidget* EquipmentWidget = MainHUD->GetEquipment(); 
			if (IsValid(EquipmentWidget))
				EquipmentWidget->LoadData(m_EquipmentItemArray);
		}
	}
}
void UAProjectGameInstance::SaveData()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();
		
		if (IsValid(MainHUD)) 
		{
			UInventoryTile* InventoryTile = MainHUD->GetInventory(); 

			if (IsValid(InventoryTile))
			{
				m_EquipItemList = InventoryTile->GetEquipItemList();
				m_CurrentEquipList = InventoryTile->GetCurrentEquipItemList();
				m_ConsumItemList = InventoryTile->GetConsumItemList();
			}

			UEquipmentWidget* EquipmentWidget = MainHUD->GetEquipment();

			if (IsValid(EquipmentWidget))
			{
				m_EquipmentItemArray = EquipmentWidget->GetItemArray();
			}
		}
	}
}