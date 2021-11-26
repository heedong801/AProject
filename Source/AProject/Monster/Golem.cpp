// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem.h"
#include "GolemAIController.h"

AGolem::AGolem()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Red/Meshes/Buff_Red.Buff_Red'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("Golem");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/Golem/AB_Golem.AB_Golem_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = AGolemAIController::StaticClass();

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));*/
}

// Called when the game starts or when spawned
void AGolem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGolem::NormalAttack()
{
	/*FVector MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMinionGunnerBullet* Bullet = GetWorld()->SpawnActor<AMinionGunnerBullet>(
		AMinionGunnerBullet::StaticClass(), MuzzleLoc, GetActorRotation(), param);

	Bullet->SetAttack(m_MonsterInfo.Attack);
	Bullet->SetMonster(this);*/
}

void AGolem::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);

	Destroy();
}