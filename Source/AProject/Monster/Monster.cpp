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

	////�������
	//if (m_MonsterInfo.HP <= 0)
	//{
	//	ChangeAnimType(EMonsterAnimType::Death);

	//	AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
	//	if (MonsterController)
	//		MonsterController->BrainComponent->StopLogic(TEXT("Dead"));

	//	// ���Ͱ� �׾��� ��� ����Ʈ�� �ش� ���͸� ��� ����Ʈ�� �ִ��� �Ǵ��Ѵ�.
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

	//	// �������� ���;� ���� ���ƾ� ���� �����Ѵ�.
	//	float Percent = FMath::RandRange(0.f, 100.f);

	//	if (Percent <= 100.f)
	//	{
	//		// �������� ���;� �Ѵٸ� � �������� ������ �Ұ����� �����Ѵ�.
	//		//Percent = FMath::RandRange(0.f, 100.f);
	//		int32	Index = FMath::RandRange(0, m_DropItemNameArray.Num() - 1);

	//		UUEKR2GameInstance* GmaeInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

	//		if (GmaeInst)
	//		{
	//			const FUIItemTableInfo* ItemInfo = GmaeInst->FindUIItemInfo(m_DropItemNameArray[Index]);
	//			//LOG(TEXT("INDEX : %d"), Index);

	//			if (ItemInfo)
	//			{
	//				// ������ ���ڸ� �����Ѵ�.
	//				FActorSpawnParameters	param;
	//				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//				FBox	SpawnBox(GetMesh()->GetComponentLocation() - FVector(50.f, 50.f, -200.f),
	//					GetMesh()->GetComponentLocation() + FVector(50.f, 50.f, 200.f));

	//				// Ghost Trail ����
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