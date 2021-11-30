// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectGameInstance.h"

UAProjectGameInstance::UAProjectGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTableAsset(TEXT("DataTable'/Game/Monster/DT_MonsterInfo.DT_MonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTableAsset(TEXT("DataTable'/Game/Player/DT_PlayerInfo.DT_PlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
}

UAProjectGameInstance::~UAProjectGameInstance()
{

}
const FMonsterInfo* UAProjectGameInstance::FindMonsterInfo(const FString& Name)
{
	return m_MonsterInfoTable->FindRow<FMonsterInfo>(*Name, "");
}


const FPlayerInfo* UAProjectGameInstance::FindPlayerInfo(const FString& Name)
{
	return m_PlayerInfoTable->FindRow<FPlayerInfo>(*Name, "");
}

//const FUIItemTableInfo* UAProjectGameInstance::FindUIItemInfo(const FString& Name)
//{
//	return m_UIItemInfoTable->FindRow<FUIItemTableInfo>(*Name, "");
//}
//
//const FQuestTableInfo* UAProjectGameInstance::FindQuestInfo(const FString& Name)
//{
//	return m_QuestInfoTable->FindRow<FQuestTableInfo>(*Name, "");
//}