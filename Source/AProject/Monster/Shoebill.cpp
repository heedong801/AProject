// Fill out your copyright notice in the Description page of Project Settings.


#include "Shoebill.h"

AShoebill::AShoebill()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Black/Meshes/Buff_Black.Buff_Black'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	/*static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BP_MinionWarriorAnim.BP_MinionWarriorAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);*/

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF���"));
	m_DropItemNameArray.Add(TEXT("HP����"));*/
}

// Called when the game starts or when spawned
void AShoebill::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AShoebill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShoebill::NormalAttack()
{
	/*FVector MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMinionGunnerBullet* Bullet = GetWorld()->SpawnActor<AMinionGunnerBullet>(
		AMinionGunnerBullet::StaticClass(), MuzzleLoc, GetActorRotation(), param);

	Bullet->SetAttack(m_MonsterInfo.Attack);
	Bullet->SetMonster(this);*/
}