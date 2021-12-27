// Fill out your copyright notice in the Description page of Project Settings.


#include "Barghest.h"
#include "BarghestAIController.h"
#include "../AProjectGameModeBase.h"
#include "../Effect/NormalEffect.h"
#include "../DebugClass.h"
#include "../Building/Nexus.h"

ABarghest::ABarghest()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/QuadrapedCreatures/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	m_MonsterInfoName = TEXT("Barghest");

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Monster/Barghest/AB_Barhest.AB_Barhest_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = ABarghestAIController::StaticClass();

	/*m_MonsterInfoName = TEXT("MinionWorrior");

	m_DropItemNameArray.Add(TEXT("BF���"));
	m_DropItemNameArray.Add(TEXT("HP����"));*/
}

ABarghest::~ABarghest()
{
	LOG(TEXT("DOE"));
}
// Called when the game starts or when spawned
void ABarghest::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABarghest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarghest::NormalAttack()
{
	FVector MinionLoc = GetActorLocation();
	FVector Forward = GetActorForwardVector();

	FCollisionQueryParams params(NAME_None, false, this);
	// ���� �������� �� Ÿ�ֿ̹� �浹ó���� ���ֵ��� �Ѵ�. 
	FHitResult HitResult;
	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult,
		MinionLoc, MinionLoc + Forward * m_MonsterInfo.DamageDistance, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4
		, FCollisionShape::MakeSphere(30.f),
		params);

	//PrintViewport(1.0f, FColor::Red, TEXT("ASDASD"));
#if ENABLE_DRAW_DEBUG
	/*FColor DrawColor = Sweep ? FColor::Red : FColor::Green;

	FVector Center = MinionLoc + Forward * m_MonsterInfo.AttackDistance * 0.5f;
	DrawDebugCapsule(GetWorld(), Center, m_MonsterInfo.DamageDistance * 0.5f, 30.f,
		FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor,
		false, 0.5f);*/
	//DrawDebugCone(GetWorld(), MinionLoc, GetActorForwardVector(), m_PlayerInfo.AttackDistance, FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), 20, DrawColor, false, 1.f);
	//DrawDebugSphere(GetWorld(), MinionLoc, m_PlayerInfo.AttackDistance, 20, DrawColor, false, 1.f);
#endif

	if (Sweep)
	{
		//PrintViewport(1.0f, FColor::Red, TEXT("ZZZZZZZZZZZZZZZ"));

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ANormalEffect::StaticClass()));
		if (Effect != nullptr)
			Effect->LoadParticleAsync(TEXT("Buff_Red"));

		//���� �ε�
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

		//������ ����
		FDamageEvent DmgEvent;
		ANexus* Nexus = Cast<ANexus>(HitResult.GetActor());

		if (!Nexus)
			float Damage = HitResult.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);
		else
			float Damage = Nexus->TakeDamageForNexus(m_MonsterInfo.Attack, DmgEvent, GetController(), this, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

	}
}

void ABarghest::Death()
{
	GetWorldTimerManager().ClearTimer(m_MonsterDeathTimer);


	Destroy();
}
