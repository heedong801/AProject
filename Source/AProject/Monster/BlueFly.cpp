// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueFly.h"
#include "BlueFlyAIController.h"
#include "../Effect/NormalEffect.h"
#include "../Building/Nexus.h"
#include "../Effect/BlueFlyProjectile.h"
#include "../DebugClass.h"
#include "../UI/HPBar.h"
#include "../Effect/HitCameraShake.h"
#include "../Player/PlayerCharacter.h"
#include "../AProjectGameModeBase.h"


ABlueFly::ABlueFly()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Blue/Meshes/Buff_Blue.Buff_Blue'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("BlueFly");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BlueFly/AB_BlueFly.AB_BlueFly_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = ABlueFlyAIController::StaticClass();
	//GetCapsuleComponent()->SetCapsuleHalfHeight(1.f);
	//GetCapsuleComponent()->SetCapsuleRadius(1.f);
	//LOG(TEXT("%f"), GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));*/
}

// Called when the game starts or when spawned
void ABlueFly::BeginPlay()
{
	Super::BeginPlay();
	//LOG(TEXT("%f"), GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

}

// Called every frame
void ABlueFly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlueFly::NormalAttack()
{
	// Muzzle의 위치를 얻어온다.
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	ABlueFlyProjectile* Bullet = Cast<ABlueFlyProjectile>(GameMode->GetParticlePool()->Pop(MuzzleLoc, GetActorRotation(), ABlueFlyProjectile::StaticClass()));

	if (Bullet)
	{
		Bullet->SetProjectileOwner(this);
		Bullet->SetActiveBullet(GetActorForwardVector());
		Bullet->SetAttack(m_MonsterInfo.Attack);
	}

}

void ABlueFly::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Destroy();
}

float ABlueFly::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;
	//AttackedDir.Z = 0.f;


	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(
		UHitCameraShake::StaticClass());

	if (m_HPBarWidget->GetVisibility() == ESlateVisibility::Collapsed)
		m_HPBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Damage = Damage - m_MonsterInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	m_MonsterInfo.HP -= Damage;

	//죽은경우
	if (m_MonsterInfo.HP <= 0)
	{
		ChangeAnimType(EMonsterAnimType::Death);
		AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
		if (MonsterController)
		{

			MonsterController->BrainComponent->StopLogic(TEXT("Dead"));
			MonsterController->StopMovement();
		}
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("LandScape"));

		//GetCapsuleComponent()->SetCapsuleHalfHeight(1.f);
		GetCapsuleComponent()->SetCapsuleSize(0.1f, 0.1f, true);
		//LOG(TEXT("%f"), GetCapsuleComponent()->GetScaledCapsuleHalfHeight());	
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetWorldTimerManager().SetTimer(m_MonsterDeathTimer,
			this, &ABlueFly::Death, 1.f, false, 2.0f);

		if (m_HPBarWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
			m_HPBarWidget->SetVisibility(ESlateVisibility::Collapsed);



		APlayerCharacter* Player = Cast<APlayerCharacter>(DamageCauser);
		if (Player)
		{
			Player->AddExp(m_MonsterInfo.Exp);
			Player->AddGold(m_MonsterInfo.Gold);
		}
		//// 몬스터가 죽었을 경우 퀘스트에 해당 몬스터를 잡는 퀘스트가 있는지 판단한다.
		AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{

			UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();

			if (QuestWidget)
			{

				QuestWidget->QuestCheck(EQuestType::Hunt, m_MonsterInfo.Name);
			}
		}
	}
	else
	{
		FVector  PlayerLoc = DamageCauser->GetActorLocation();
		FVector AttackedDir = GetActorLocation() - PlayerLoc;
		//AttackedDir.Normalize();

		AttackedDir *= (1000.f / m_MonsterInfo.Weight);

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

	//		UAProjectGameInstance* GmaeInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

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