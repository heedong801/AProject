// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestTrigger.h"
#include "../Quest/QuestInfo.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
#include "../AProjectGameModeBase.h"
AQuestTrigger::AQuestTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Start = false;
}

// Called when the game starts or when spawned
void AQuestTrigger::BeginPlay()
{
	Super::BeginPlay();
	m_TriggerBeginDelegate.AddDynamic(this, &AQuestTrigger::TriggerBegin);
}

void AQuestTrigger::TriggerBegin()
{
	if (m_Start == false)
	{
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());


		if (GameInst)
		{
			TMap<FString, FQuestData>* QuestMap = GameInst->GetMap();
			FQuestData	Data;
			LOG(TEXT("A"));

			const FQuestTableInfo* Info = GameInst->FindQuestInfo(TEXT("Meadow1"));

			if (Info)
			{
				LOG(TEXT("B"));

				Data.Name = Info->Name;
				Data.QuestDesc = Info->QuestDesc;
				Data.CompleteArray.RemoveAll([](FQuestDataInfo v) {return true; });
				Data.CompensationArray.RemoveAll([](FQuestCompensationInfo v) {return true; });
				for (auto& CompleteData : Info->InfoArray)
				{
					FQuestDataInfo	DataInfo;

					DataInfo.Type = CompleteData.Type;
					DataInfo.DestName = CompleteData.DestName;
					DataInfo.MaxCount = CompleteData.Count;
					DataInfo.Count = 0;
					DataInfo.Complete = false;

					Data.CompleteArray.Add(DataInfo);
				}

				for (auto& CompensationData : Info->CompensationArray)
				{
					FQuestCompensationInfo	DataInfo;

					DataInfo.Type = CompensationData.Type;
					DataInfo.Compensation = CompensationData.Compensation;

					Data.CompensationArray.Add(DataInfo);
				}

				Data.Complete = false;

				QuestMap->Add(TEXT("Meadow1"), Data);
			}


			Info = GameInst->FindQuestInfo(TEXT("Meadow2"));
			if (Info)
			{
				LOG(TEXT("C"));

				Data.Name = Info->Name;
				Data.QuestDesc = Info->QuestDesc;
				Data.CompleteArray.RemoveAll([](FQuestDataInfo v) {return true; });
				Data.CompensationArray.RemoveAll([](FQuestCompensationInfo v) {return true; });


				for (auto& CompleteData : Info->InfoArray)
				{
					FQuestDataInfo	DataInfo;

					DataInfo.Type = CompleteData.Type;
					DataInfo.DestName = CompleteData.DestName;
					DataInfo.MaxCount = CompleteData.Count;
					DataInfo.Count = 0;
					DataInfo.Complete = false;

					Data.CompleteArray.Add(DataInfo);
				}

				for (auto& CompensationData : Info->CompensationArray)
				{
					FQuestCompensationInfo	DataInfo;

					DataInfo.Type = CompensationData.Type;
					DataInfo.Compensation = CompensationData.Compensation;

					Data.CompensationArray.Add(DataInfo);
				}

				Data.Complete = false;
				QuestMap->Add(TEXT("Meadow2"), Data);
			}
		}
	}

	AAProjectGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AAProjectGameModeBase>();

	if (GameMode)
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (MainHUD)
		{
			MainHUD->GetQuestWidget()->QuestSet();
		}
	}

}
