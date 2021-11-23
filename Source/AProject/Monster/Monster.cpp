// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../AProjectGameModeBase.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//if (Damage == 0.f)
	//	return 0.f;

	//Damage = Damage - m_MonsterInfo.Armor;
	//Damage = Damage < 1.f ? 1.f : Damage;

	//m_MonsterInfo.HP -= Damage;

	////죽은경우
	//if (m_MonsterInfo.HP <= 0)
	//{
	//	ChangeAnimType(EMonsterAnimType::Death);

	//	AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
	//	if (MonsterController)
	//		MonsterController->BrainComponent->StopLogic(TEXT("Dead"));

	//	// 몬스터가 죽었을 경우 퀘스트에 해당 몬스터를 잡는 퀘스트가 있는지 판단한다.
	//	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	//	if (GameMode)
	//	{

	//		UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();

	//		if (QuestWidget)
	//		{

	//			QuestWidget->QuestCheck(EQuestType::Hunt, m_MonsterInfo.Name);
	//		}
	//	}

	//	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//	// 아이템이 나와야 할지 말아야 할지 결정한다.
	//	float Percent = FMath::RandRange(0.f, 100.f);

	//	if (Percent <= 100.f)
	//	{
	//		// 아이템이 나와야 한다면 어떤 아이템을 나오게 할것인지 결정한다.
	//		//Percent = FMath::RandRange(0.f, 100.f);
	//		int32	Index = FMath::RandRange(0, m_DropItemNameArray.Num() - 1);

	//		UUEKR2GameInstance* GmaeInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	//		if (GmaeInst)
	//		{
	//			const FUIItemTableInfo* ItemInfo = GmaeInst->FindUIItemInfo(m_DropItemNameArray[Index]);
	//			//LOG(TEXT("INDEX : %d"), Index);

	//			if (ItemInfo)
	//			{
	//				// 아이템 상자를 생성한다.
	//				FActorSpawnParameters	param;
	//				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//				FBox	SpawnBox(GetMesh()->GetComponentLocation() - FVector(50.f, 50.f, -200.f),
	//					GetMesh()->GetComponentLocation() + FVector(50.f, 50.f, 200.f));

	//				// Ghost Trail 생성
	//				AItemBox* ItemBox = GetWorld()->SpawnActor<AItemBox>(AItemBox::StaticClass(),
	//					FMath::RandPointInBox(SpawnBox),
	//					GetMesh()->GetComponentRotation(), param);

	//				if (ItemBox != NULL)
	//				{
	//					ItemBox->SetMesh(ItemInfo->Mesh);
	//					ItemBox->SetItemName(m_DropItemNameArray[Index]);
	//				}

	//				PrintViewport(10.f, FColor::Blue, FString::Printf(TEXT("DropItem : %s"), *ItemInfo->Name));
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	m_AnimInstance->SetHit();
	//}

	//if (IsValid(m_HPBarWidget))
	//{

	//	m_HPBarWidget->SetHPPercent(m_MonsterInfo.HP / (float)m_MonsterInfo.HPMax);
	//}
	return 0.f;
}

void AMonster::ChangeAnimType(EMonsterAnimType Type)
{
	//m_AnimInstance->ChangeAnimType(Type);
}

FVector AMonster::GetPatrolPoint()
{
	if (m_PatrolIdx >= m_PatrolArray.Num())
		m_PatrolIdx = 0;

	return m_PatrolArray[m_PatrolIdx];
}

void AMonster::NextPatrolPoint()
{
	++m_PatrolIdx;
	++m_CurrentPatrolIndex;

	if (m_PatrolIdx >= m_PatrolArray.Num())
		m_PatrolIdx = 0;

	if (m_CurrentPatrolIndex >= 3)
		m_CurrentPatrolIndex = 0;
}