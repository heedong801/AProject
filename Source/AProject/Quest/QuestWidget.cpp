// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "../AProjectGameInstance.h"
#include "QuestListItemData.h"
#include "QuestListItemWidget.h"
#include "../Player/PlayerCharacter.h"
//#include "InventoryList.h"
//#include "InventoryTile.h"
#include "../AProjectGameModeBase.h"
#include "../UI/MainHUD.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_QuestList = Cast<UListView>(GetWidgetFromName(TEXT("QuestList")));
	m_QuestDesc = Cast<UQuestDescWidget>(GetWidgetFromName(TEXT("UI_QuestDesc")));

	m_QuestList->OnItemClicked().AddUObject(this, &UQuestWidget::QuestClick);
	m_QuestList->OnItemSelectionChanged().AddUObject(this, &UQuestWidget::QuestSelect);
	m_QuestList->OnItemIsHoveredChanged().AddUObject(this, &UQuestWidget::QuestMouseOn);

	m_CurrentRenderQuest = nullptr;


	m_PrevSelect = nullptr;
}

void UQuestWidget::QuestSet()
{
	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const TMap<FString, FQuestData>& QuestData = GameInst->GetQuestData();

		int32	Index = 0;

		for (auto& Data : QuestData)
		{
			const FQuestTableInfo* Info = GameInst->FindQuestInfo(Data.Key);

			if (Info)
			{
				m_QuestArray.Add(Data.Value);

				int32	QuestIndex = m_QuestArray.Num() - 1;

				for (auto& QuestInfo : Info->InfoArray)
				{
					m_QuestListArray[(uint8)QuestInfo.Type].Add(&m_QuestArray[QuestIndex]);
				}

				UQuestListItemData* QuestItemData = NewObject<UQuestListItemData>(this,
					UQuestListItemData::StaticClass());

				QuestItemData->SetIndex(Index);
				QuestItemData->SetQuestName(Info->Name);

				m_QuestList->AddItem(QuestItemData);

				++Index;
			}
		}
	}
}
void UQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestWidget::QuestClick(UObject* Data)
{
	UQuestListItemData* Info = Cast<UQuestListItemData>(Data);

	if (Info)
	{
		if (m_CurrentRenderQuest == &m_QuestArray[Info->GetIndex()])
			return;

		m_CurrentRenderQuest = &m_QuestArray[Info->GetIndex()];

		FString	QuestName = m_QuestArray[Info->GetIndex()].Name;

		if (m_CurrentRenderQuest->Complete)
			QuestName = m_QuestArray[Info->GetIndex()].Name + TEXT("(완료)");

		m_QuestDesc->SetQuestName(QuestName);
		m_QuestDesc->SetQuestDesc(m_QuestArray[Info->GetIndex()].QuestDesc);

		m_QuestDesc->ClearList();

		int32	Index = 0;

		for (auto& DataInfo : m_QuestArray[Info->GetIndex()].CompleteArray)
		{
			m_QuestDesc->AddList(DataInfo, Index);
			++Index;
		}
	}
}

void UQuestWidget::QuestSelect(UObject* Data)
{
	UQuestListItemData* Item = Cast<UQuestListItemData>(Data);
	//PrintViewport(5.f, FColor::Red, Item->GetQuestName());

	if (m_PrevSelect)
		m_PrevSelect->GetOwnerWidget()->Select(false);

	Item->GetOwnerWidget()->Select(true);

	m_PrevSelect = Item;
}

void UQuestWidget::QuestMouseOn(UObject* Data, bool IsHovered)
{
	UQuestListItemData* Item = Cast<UQuestListItemData>(Data);

	Item->GetOwnerWidget()->MouseOn(IsHovered);
}

void UQuestWidget::QuestCheck(EQuestType Type, const FString& Name)
{
	for (auto& Info : m_QuestListArray[(uint8)Type])
	{

		if (Info->Complete)
			continue;

		int32	CompleteCount = 0;

		for (auto& QuestData : Info->CompleteArray)
		{
		
			if (QuestData.Complete)
			{
			
				++CompleteCount;
				continue;
			}
		

			if (QuestData.Type == Type && QuestData.DestName == Name)
			{
				++QuestData.Count;
				//PrintViewport(5.0f, FColor::Red, TEXT("FFFFFFFFFFF"));

				if (QuestData.Count == QuestData.MaxCount)
				{
					QuestData.Complete = true;
					++CompleteCount;
				}

				// 현재 퀘스트창에 보여지고 있는 퀘스트가 변경이 일어났을 경우
				// 갱신한다.
				if (m_CurrentRenderQuest == Info)
				{
					//PrintViewport(5.0f, FColor::Red, TEXT("EEEEEEEEEEEEEEEEEE"));

					m_QuestDesc->SetQuestName(m_CurrentRenderQuest->Name);
					m_QuestDesc->SetQuestDesc(m_CurrentRenderQuest->QuestDesc);

					m_QuestDesc->ClearList();

					int32	CompleteIndex = 0;

					for (auto& DataInfo : m_CurrentRenderQuest->CompleteArray)
					{
						m_QuestDesc->AddList(DataInfo, CompleteIndex);
						++CompleteIndex;
					}
				}
			}
		}
		//PrintViewport(5.0f, FColor::Red, TEXT("EXITTTTTTTTTT"));

		if (CompleteCount == Info->CompleteArray.Num())
		{
			//PrintViewport(5.0f, FColor::Red, TEXT("STARRRRRRT"));

			Info->Complete = true;

			// 퀘스트 완료시 보상 처리

			for (auto& CompensationData : Info->CompensationArray)
			{
				//PrintViewport(5.0f, FColor::Red, TEXT("AAAAAAAAAAAAAAAA"));

				switch (CompensationData.Type)
				{
				case EQuestCompensationType::Gold:
				{
					//PrintViewport(1.0f, FColor::Red, TEXT("BBBBBBBBBBBBB"));

					int32	Gold = FCString::Atoi(*CompensationData.Compensation);

					APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();

					if (Player)
						Player->AddGold(Gold);
				}
				break;
				case EQuestCompensationType::Item:
				{
					UAProjectGameInstance* GameInst = GetWorld()->GetGameInstance<UAProjectGameInstance>();

					if (GameInst)
					{
						/*const FUIItemTableInfo* ItemInfo = GameInst->FindUIItemInfo(CompensationData.Compensation);

						if (ItemInfo)
						{
							AAProjectGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AAProjectGameModeBase>();

							if (GameMode)
							{
								UMainHUD* MainHUD = GameMode->GetMainHUD();

								if (MainHUD)
								{
									MainHUD->GetInventoryList()->AddItem(ItemInfo);
								}
							}
						}*/
					}
				}
				break;
				case EQuestCompensationType::Exp:
				{
					int32	Exp = FCString::Atoi(*CompensationData.Compensation);

					APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();

					if (Player)
						Player->AddExp(Exp);
				}
				break;
				}
			}
		}
	}
}
