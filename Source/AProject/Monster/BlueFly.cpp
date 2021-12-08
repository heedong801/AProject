// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueFly.h"
#include "BlueFlyAIController.h"
#include "../AProjectGameInstance.h"
#include "../Effect/NormalEffect.h"
#include "../Building/Nexus.h"

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

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));*/
}

// Called when the game starts or when spawned
void ABlueFly::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABlueFly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlueFly::NormalAttack()
{
	//// Muzzle의 위치를 얻어온다.
	//FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));

	//FActorSpawnParameters	param;
	//param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//AMinionGunnerBullet* Bullet = GetWorld()->SpawnActor<AMinionGunnerBullet>(
	//	AMinionGunnerBullet::StaticClass(), MuzzleLoc, GetActorRotation(),
	//	param);

	//Bullet->SetAttack(m_MonsterInfo.Attack);
	//Bullet->SetOwner(this);
}

void ABlueFly::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);

	Destroy();
}
