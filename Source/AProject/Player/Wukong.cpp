// Fill out your copyright notice in the Description page of Project Settings.


#include "Wukong.h"
#include "../Effect/NormalEffect.h"
#include "../DebugClass.h"
AWukong::AWukong()
	: m_MaxCombo(5), m_CurrentCombo(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WukongMesh(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Meshes/Wukong.Wukong'"));

	if (WukongMesh.Succeeded())
		GetMesh()->SetSkeletalMesh((WukongMesh.Object));

	m_PlayerInfo.Name = TEXT("Wukong");
	m_PlayerInfo.Job = EPlayerJob::Knight;
	m_PlayerInfo.Attack = 40;
	m_PlayerInfo.Armor = 20;
	m_PlayerInfo.HP = 500;
	m_PlayerInfo.HPMax = 500;
	m_PlayerInfo.MP = 100;
	m_PlayerInfo.MPMax = 100;
	m_PlayerInfo.AttackDistance = 200.f;
	m_PlayerInfo.AttackSpeed = 1.f;
	m_PlayerInfo.MoveSpeed = 600.f;
	m_PlayerInfo.AttackAngle = 60.f;
}

// Called when the game starts or when spawned
void AWukong::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWukong::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWukong::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWukong::SetCurrentCombo(int32 curCombo) 
{
	m_CurrentCombo = curCombo;
	
	m_CurrentCombo = FMath::Clamp(m_CurrentCombo, 0, m_MaxCombo);
}

void AWukong::HitDamage()
{
	Super::HitDamage();

	FVector PlayerLoc = GetActorLocation();

	FCollisionQueryParams params(NAME_None, false, this);
	// ���� �������� �� Ÿ�ֿ̹� �浹ó���� ���ֵ��� �Ѵ�. 
	TArray<FHitResult> HitResultArray;
	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, PlayerLoc, PlayerLoc, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
		, FCollisionShape::MakeSphere(m_PlayerInfo.AttackDistance), params);


	//LOG(TEXT("Attack : %.5f"), 200.f);
	//LOG(TEXT("TestAttack"));
	//PrintViewport(1.f, FColor::Yellow, TEXT("ATTACK"));
	TArray<FHitResult> CollisionArray;

	if (Sweep)
	{
		for (auto& result : HitResultArray)
		{
			//1�� �� �浹�� �Ͼ Ÿ�ϰ� ������ ���Ѵ�.
			FVector Forward = GetActorForwardVector();
			//LOG(TEXT("%.5f, %.5f, %.5f"), result.ImpactPoint.X, result.ImpactPoint.Y, result.ImpactPoint.Z);

			FVector Dir = result.ImpactPoint - GetActorLocation();
			// �������ͷ� �����. ������ ���� ���·� üũ�� �ϱ� ���ؼ� ������ üũ����� �ϴµ� 
			// ���������� ������ �̿��ϰ� �ȴٸ� �� ���Ͱ� ������ �ڻ��� ��Ÿ ���� ������ �� �ִ�.
			// �׷��Ƿ� �̷��� �ڻ��� ��Ÿ�� ��ũ�ڻ����� �̿��Ͽ� ��Ÿ�� �����ϰ� 
			// �̸� ���Ͽ� ���Ծȿ� ���������� �Ǵ��Ѵ�.
			Dir.Normalize();

			Forward.Normalize();

			float Dot = FVector::DotProduct(Dir, Forward);
			// Acos�� �̿��ϸ� ���� �����ϱ� ��׸��� �ٲ�
			float Angle = FMath::Acos(Dot);
			Angle = FMath::RadiansToDegrees(Angle);
			//LOG(TEXT("Attack : %.5f"), Angle);

			if (Angle <= m_PlayerInfo.AttackAngle)
				CollisionArray.Add(result);
			else
			{
				//�̰� �ƴ϶�� ������ �̿��ؼ� ���� �浹ü�� �����ϴ��� �Ǵ�
				//GetWorld()->LineTraceSingleByChannel();
			}

		}
	}

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = CollisionArray.Num() > 0 ? FColor::Red : FColor::Green;
	DrawDebugCone(GetWorld(), PlayerLoc, GetActorForwardVector(), m_PlayerInfo.AttackDistance, FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), 20, DrawColor, false, 1.f);
	//DrawDebugSphere(GetWorld(), PlayerLoc, m_PlayerInfo.AttackDistance, 20, DrawColor, false, 1.f);
#endif

	for (auto& result : CollisionArray)
	{

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);

		//���� �ε�
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
		Effect->LoadParticleAsync(TEXT("HitNormal"));
		//Effect->LoadSoundAsync(TEXT("HitNormal"));

		//������ ����
		FDamageEvent DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_PlayerInfo.Attack, DmgEvent, GetController(), this);

	}
}
