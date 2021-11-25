// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "MonsterAIController.h"
#include "../AProjectGameInstance.h"
#include "../AProjectGameModeBase.h"
#include "../DebugClass.h"
#include "../UI/HPBar.h"
#include "../Effect/HitCameraShake.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	m_HPBar->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget>	HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));

	if (HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f, 60.f));
	m_HPBar->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//FBox spawnBox;
	//spawnBox.BuildAABB(GetActorLocation(), FVector(1500.f, 1500.f, 1));

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	//LOG(TEXT("%f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	for (int32 i = 0; i < 4; ++i)
	{
		FVector ranVec = GetActorLocation() + FVector(FMath::RandPointInCircle(1500.f), 0.f);
		m_PatrolArray.Add(ranVec);
		//LOG(TEXT("%f %f %f"), ranVec.X, ranVec.Y, ranVec.Z);
	}

	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{

		const FMonsterInfo* Info = GameInst->FindMonsterInfo(m_MonsterInfoName);
		if (Info)
		{
			m_MonsterInfo.Name = Info->Name;
			m_MonsterInfo.Attack = Info->Attack;
			m_MonsterInfo.Armor = Info->Armor;
			m_MonsterInfo.HP = Info->HP;
			m_MonsterInfo.HPMax = Info->HPMax;
			m_MonsterInfo.MP = Info->MP;
			m_MonsterInfo.MPMax = Info->MPMax;
			m_MonsterInfo.Level = Info->Level;
			m_MonsterInfo.Exp = Info->Exp;
			m_MonsterInfo.Gold = Info->Gold;
			m_MonsterInfo.AttackDistance = Info->AttackDistance;
			m_MonsterInfo.AttackSpeed = Info->AttackSpeed;
			m_MonsterInfo.AttackAngle = Info->AttackAngle;
			m_MonsterInfo.MoveSpeed = Info->MoveSpeed;
			m_MonsterInfo.TraceDistance = Info->TraceDistance;

		}
	}

	m_AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());

	m_HPBarWidget->SetName(m_MonsterInfoName);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LOG(TEXT("%f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	//if (!m_Monster)
	//{
	//	m_AccTime += DeltaTime;

	//	if (m_AccTime >= m_SpawnTime)
	//	{
	//		m_AccTime = 0.f;

	//		FActorSpawnParameters	param;
	//		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//		AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClass,
	//			GetActorLocation(), GetActorRotation(), param);

	//		Monster->SetSpawnPoint(this);

	//		if (m_PatrolPointSpline)
	//		{
	//			Monster->SetPatrolPointSpline(m_PatrolPointSpline);
	//			Monster->SetPatrolLength(m_PatrolPointSpline->GetSplineLength());

	//			//Monster->AddPatrolPoint(GetActorLocation());

	//			const TArray<FVector>& PatrolPointArray = m_PatrolPointSpline->GetPointArray();

	//			for (auto& Point : PatrolPointArray)
	//			{
	//				Monster->AddPatrolPoint(Point);
	//			}
	//		}

	//		else
	//		{
	//			Monster->AddPatrolPoint(GetActorLocation());

	//			for (auto& Point : m_PatrolPointArray)
	//			{
	//				Monster->AddPatrolPoint(Point->GetActorLocation());
	//			}
	//		}


	//		m_Monster = Monster;
	//	}
	//}

}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;
	//AttackedDir.Z = 0.f;

	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(
		UHitCameraShake::StaticClass());

	if (m_HPBarWidget->GetVisibility() == ESlateVisibility::Collapsed)
		m_HPBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Damage = Damage - m_MonsterInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	m_MonsterInfo.HP -= Damage;

	
	//죽은경우
	if (m_MonsterInfo.HP <= 0)
	{
		//Death();
		if (m_HPBarWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
			m_HPBarWidget->SetVisibility(ESlateVisibility::Collapsed);

		ChangeAnimType(EMonsterAnimType::Death);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(m_MonsterDeathTimer,
			this, &AMonster::Death, 2.f, true);

		//AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
		//if (MonsterController)
		//	MonsterController->BrainComponent->StopLogic(TEXT("Dead"));

		//// 몬스터가 죽었을 경우 퀘스트에 해당 몬스터를 잡는 퀘스트가 있는지 판단한다.
		//AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

		//if (GameMode)
		//{

		//	UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();

		//	if (QuestWidget)
		//	{

		//		QuestWidget->QuestCheck(EQuestType::Hunt, m_MonsterInfo.Name);
		//	}
	}
	else
	{
		FVector  PlayerLoc = DamageCauser->GetActorLocation();
		FVector AttackedDir = GetActorLocation() - PlayerLoc;
		//AttackedDir.Normalize();
		AttackedDir *= 10.f;

		LaunchCharacter(AttackedDir, false, false);
	}
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


	if (IsValid(m_HPBarWidget))
	{

		m_HPBarWidget->SetHPPercent(m_MonsterInfo.HP / (float)m_MonsterInfo.HPMax);
	}
	return Damage;
}

void AMonster::ChangeAnimType(EMonsterAnimType Type)
{
	m_AnimInstance->ChangeAnimType(Type);
}

FVector AMonster::NextPatrolPoint()
{
	while (true)
	{
		int random = FMath::RandRange(0, 3);
		if (random == m_PatrolIdx)
			continue;
		else
		{
			m_PatrolIdx = random;
			break;
		}
	}

	return m_PatrolArray[m_PatrolIdx];
}

FVector AMonster::GetPatrolPoint()
{
	return m_PatrolArray[m_PatrolIdx];
}

