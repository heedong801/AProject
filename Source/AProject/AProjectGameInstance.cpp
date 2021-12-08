// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectGameInstance.h"
#include "DebugClass.h"
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
}

void UAProjectGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

void UAProjectGameInstance::SetParticlePool( UParticlePool* pParticlePool)
{
	/*LOG(TEXT("%s"), *pP->GetName());
	if(pP->GetSize() == 0 )
		pP->MakePool();

	LOG(TEXT("%d"), pP->GetSize());*/

	m_ParticlePool = pParticlePool;
	if (m_ParticlePool->GetSize() == 0)
		m_ParticlePool->MakePool();
	
}

int UAProjectGameInstance::GetPoolSize()
{
	return m_ParticlePool->GetSize();
}

//void UAProjectGameInstance::SetParticlePool()
//{
//	LOG(TEXT("%s"), *m_ParticlePool->GetName());
//	if (m_ParticlePool->GetSize() == 0)
//		m_ParticlePool->MakePool();
//
//	LOG(TEXT("%d"), m_ParticlePool->GetSize());
//}

bool UAProjectGameInstance::StartPIEGameInstance(ULocalPlayer* LocalPlayer, bool bInSimulateInEditor, bool bAnyBlueprintErrors, bool bStartInSpectatorMode)
{
	bool result = Super::StartPIEGameInstance(LocalPlayer, bInSimulateInEditor, bAnyBlueprintErrors, bStartInSpectatorMode);

	return result;
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
const FQuestTableInfo* UAProjectGameInstance::FindQuestInfo(const FString& Name)
{
	return m_QuestInfoTable->FindRow<FQuestTableInfo>(*Name, "");
}

const FMapTableInfo* UAProjectGameInstance::FindMapInfo(const FString& Name)
{
	return m_MapInfoTable->FindRow<FMapTableInfo>(*Name, "");
}