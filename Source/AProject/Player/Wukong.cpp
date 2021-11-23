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
	// 근접 공격으로 이 타이밍에 충돌처리를 해주도록 한다. 
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
			//1차 구 충돌이 일어난 타켓과 각도를 구한다.
			FVector Forward = GetActorForwardVector();
			//LOG(TEXT("%.5f, %.5f, %.5f"), result.ImpactPoint.X, result.ImpactPoint.Y, result.ImpactPoint.Z);

			FVector Dir = result.ImpactPoint - GetActorLocation();
			// 단위벡터로 만든다. 이유는 원뿔 형태로 체크를 하기 위해서 각도를 체크해줘야 하는데 
			// 단위벡터의 내적을 이용하게 된다면 두 벡터간 각도의 코사인 세타 값을 구해줄 수 있다.
			// 그러므로 이러한 코사인 세타를 아크코사인을 이용하여 세타로 변경하고 
			// 이를 비교하여 원뿔안에 들어오는지를 판단한다.
			Dir.Normalize();

			Forward.Normalize();

			float Dot = FVector::DotProduct(Dir, Forward);
			// Acos를 이용하면 라디안 나오니까 디그리로 바꿈
			float Angle = FMath::Acos(Dot);
			Angle = FMath::RadiansToDegrees(Angle);
			//LOG(TEXT("Attack : %.5f"), Angle);

			if (Angle <= m_PlayerInfo.AttackAngle)
				CollisionArray.Add(result);
			else
			{
				//이게 아니라면 직선을 이용해서 상대방 충돌체를 관통하는지 판단
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

		//에셋 로딩
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
		Effect->LoadParticleAsync(TEXT("HitNormal"));
		//Effect->LoadSoundAsync(TEXT("HitNormal"));

		//데미지 전달
		FDamageEvent DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_PlayerInfo.Attack, DmgEvent, GetController(), this);

	}
}
