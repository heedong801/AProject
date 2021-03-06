// Fill out your copyright notice in the Description page of Project Settings.


#include "Shoebill.h"
#include "ShoebillAIController.h"
#include "../AProjectGameModeBase.h"
#include "../Effect/NormalEffect.h"
#include "../Building/Nexus.h"

AShoebill::AShoebill()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Black/Meshes/Buff_Black.Buff_Black'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("Shoebill");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/Shoebill/AB_Shoebill.AB_Shoebill_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = AShoebillAIController::StaticClass();

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF대검"));
	m_DropItemNameArray.Add(TEXT("HP포션"));*/
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
	FVector MinionLoc = GetActorLocation();
	FVector Forward = GetActorForwardVector();

	FCollisionQueryParams params(NAME_None, false, this);
	// 근접 공격으로 이 타이밍에 충돌처리를 해주도록 한다. 
	FHitResult HitResult;
	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult,
		MinionLoc, MinionLoc + Forward * m_MonsterInfo.DamageDistance, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4
		, FCollisionShape::MakeSphere(30.f),
		params);

	//PrintViewport(1.0f, FColor::Red, TEXT("ASDASD"));


	if (Sweep)
	{
		//PrintViewport(1.0f, FColor::Red, TEXT("ZZZZZZZZZZZZZZZ"));

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ANormalEffect::StaticClass()));
		if (Effect != nullptr)
			Effect->LoadParticleAsync(TEXT("Buff_Black"));

		//에셋 로딩
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

		//데미지 전달
		FDamageEvent DmgEvent;
		ANexus* Nexus = Cast<ANexus>(HitResult.GetActor());

		if (!Nexus)
			float Damage = HitResult.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);
		else
			float Damage = Nexus->TakeDamageForNexus(m_MonsterInfo.Attack, DmgEvent, GetController(), this, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

	}
}

void AShoebill::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);

	Destroy();
}