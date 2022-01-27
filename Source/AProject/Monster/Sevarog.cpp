// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevarog.h"

ASevarog::ASevarog()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Skins/Tier_1/Sevarog_Chronos/Meshes/SevarogChronos.SevarogChronos'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("Sevarog");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/Sevarog/AB_Sevarog.AB_Sevarog_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	//AIControllerClass = AOmnikAIController::StaticClass();
}

// Called when the game starts or when spawned
void ASevarog::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASevarog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASevarog::NormalAttack()
{
	
}

void ASevarog::Death()
{

}