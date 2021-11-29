// Fill out your copyright notice in the Description page of Project Settings.


#include "Omnik.h"
#include "OmnikAIController.h"

AOmnik::AOmnik()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_White/Meshes/Buff_White.Buff_White'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("Omnik");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/Omnik/AB_Omnik.AB_Omnik_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = AOmnikAIController::StaticClass();

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));*/
}

// Called when the game starts or when spawned
void AOmnik::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AOmnik::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOmnik::NormalAttack()
{
	/*FVector MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMinionGunnerBullet* Bullet = GetWorld()->SpawnActor<AMinionGunnerBullet>(
		AMinionGunnerBullet::StaticClass(), MuzzleLoc, GetActorRotation(), param);

	Bullet->SetAttack(m_MonsterInfo.Attack);
	Bullet->SetMonster(this);*/
}

void AOmnik::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);

	Destroy();
}