// Fill out your copyright notice in the Description page of Project Settings.


#include "Wukong.h"
#include "../Effect/NormalEffect.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
#include "PlayerAnim.h"
#include "../Effect/HitCameraShake.h"
#include "../AProjectGameModeBase.h"
AWukong::AWukong()
	: m_MaxCombo(5), m_CurrentCombo(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WukongMesh(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Meshes/Wukong.Wukong'"));

	if (WukongMesh.Succeeded())
		GetMesh()->SetSkeletalMesh((WukongMesh.Object));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	WukongAnimAsset(TEXT("AnimBlueprint'/Game/Player/Wukong/Anim/AB_Wukong.AB_Wukong_C'"));

	if (WukongAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(WukongAnimAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_AttackA.AM_AttackA'"));

	if (Attack1Asset.Succeeded())
		m_AttackMontage = Attack1Asset.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SkyAttackAsset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_SkyAttack.AM_SkyAttack'"));

	if (SkyAttackAsset.Succeeded())
		m_SkyAttackMontage = SkyAttackAsset.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_Lighteningbolt.AM_Lighteningbolt'"));

	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);

	m_PlayerInfoName = TEXT("Wukong");
	//m_PlayerInfo.Name = TEXT("Wukong");
	//m_PlayerInfo.Job = EPlayerJob::Knight;
	//m_PlayerInfo.Attack = 40;
	//m_PlayerInfo.Armor = 20;
	//m_PlayerInfo.HP = 500;
	//m_PlayerInfo.HPMax = 500;
	//m_PlayerInfo.MP = 100;
	//m_PlayerInfo.MPMax = 100;
	//m_PlayerInfo.AttackDistance = 200.f;
	//m_PlayerInfo.AttackSpeed = 1.f;
	//m_PlayerInfo.MoveSpeed = 600.f;
	//m_PlayerInfo.AttackAngle = 60.f;

	//m_ParticlePool = CreateDefaultSubobject<UParticlePool>(TEXT("ParticlePool"));
	
	m_BoltCnt = 0;
}

// Called when the game starts or when spawned
void AWukong::BeginPlay()
{
	Super::BeginPlay();
	/*LOG(TEXT("%s"), *m_ParticlePool->GetName());
	if (m_ParticlePool->GetSize() == 0)
		m_ParticlePool->MakePool();

	LOG(TEXT("%d"), m_ParticlePool->GetSize());*/


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
	m_LaunchPower = 1.0f;
	for (auto& result : CollisionArray)
	{

		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);*/

		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(result.ImpactPoint, result.ImpactNormal.Rotation(), ANormalEffect::StaticClass()));
		 if( Effect != nullptr )
			 Effect->LoadParticleAsync(TEXT("HitFire"));
		//에셋 로딩
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/ParagonSunWukong/FX/Particles/Wukong/Abilities/Primary/FX/P_Wukong_Impact_Empowered.P_Wukong_Impact_Empowered'"));
		//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
		
		//Effect->LoadSoundAsync(TEXT("HitNormal"));
		//데미지 전달
		FDamageEvent DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_PlayerInfo.Attack, DmgEvent, GetController(), this);

	}
}

void AWukong::UseSkill(int32 Idx)
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

			if (IsValid(CharacterHUD))
			{
				//LOG(TEXT("AAAAAAAAAAAAA"));
				m_PlayerInfo.MP -= 20;
				CharacterHUD->SetMPPercent(m_PlayerInfo.MP / (float)m_PlayerInfo.MPMax);
			}
		}
	}

	if (m_PlayerInfo.MP > 20)
	{
		switch (Idx)
		{
		case 0:
		{
			GetWorld()->GetTimerManager().SetTimer(m_BoltTimerHandler,
				this, &AWukong::LighteningBolt, 0.05f, true, 0.f);
			m_BoltCnt = 0;
			//LOG(TEXT("A"));
			//m_AnimInst->Montage_JumpToSection(TEXT("Start"), m_SkillMontageArray[0]);
			break;
		}
		}
	}
}

void AWukong::LighteningBolt()
{
	m_BoltCnt++;
	if (m_BoltCnt > 100)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_BoltTimerHandler);
		//LOG(TEXT("B"));

		m_AnimInst->Montage_JumpToSection(TEXT("End"), m_SkillMontageArray[0]);
		
	}
	else
	{
		FCollisionQueryParams params(NAME_None, false, this);

		TArray<FHitResult> HitResultArray;
		bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
			, FCollisionShape::MakeSphere(3000.f), params);
		//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(UHitCameraShake::StaticClass());
		m_LaunchPower = 5.0f;
		for (auto result : HitResultArray)
		{
			if (Sweep)
			{
				//ANormalEffect* Effect3 = GameInst->GetParticlePool()->Pop(result.ImpactPoint, result.ImpactNormal.Rotation());

				//에셋 로딩
				//Effect3->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));
				//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
				//Effect3->LoadParticleAsync(TEXT("HitNormal"));
				//Effect->LoadSoundAsync(TEXT("HitNormal"));

				//데미지 전달
				FDamageEvent DmgEvent;
				float Damage = result.GetActor()->TakeDamage(50, DmgEvent, GetController(), this);
			}
		}

		float RandomX = FMath::RandRange(-1000.f, 1000.f);
		float RandomY = FMath::RandRange(-1000.f, 1000.f);

		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(GetActorLocation() + FVector(RandomX,RandomY,0), GetActorRotation(), ANormalEffect::StaticClass()));
		if (Effect != nullptr)
			Effect->LoadParticleAsync(TEXT("Player_Bolt"));
	}
}