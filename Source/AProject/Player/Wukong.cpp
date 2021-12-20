// Fill out your copyright notice in the Description page of Project Settings.


#include "Wukong.h"
#include "../Effect/NormalEffect.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
#include "PlayerAnim.h"
#include "../Effect/HitCameraShake.h"
#include "../AProjectGameModeBase.h"
#include "../Effect/BoltDecal.h"
#include "../Effect/WukongAttackProjectile.h"
AWukong::AWukong()
	: m_MaxCombo(5), m_CurrentCombo(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_FuryWukongMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FuryMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	FuryMesh(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Skins/GreatSage/Meshes/Wukong_GreatSage.Wukong_GreatSage'"));
	if (FuryMesh.Succeeded())
		m_FuryWukongMesh->SetSkeletalMesh(FuryMesh.Object);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WukongMesh(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Meshes/Wukong.Wukong'"));
	if (WukongMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(WukongMesh.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	WukongAnimAsset(TEXT("AnimBlueprint'/Game/Player/Wukong/Anim/AB_Wukong.AB_Wukong_C'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance>	FuryWukongAnimAsset(TEXT("AnimBlueprint'/Game/Player/Wukong/Anim/AB_Wukong.AB_Wukong_C'"));

	if (WukongAnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WukongAnimAsset.Class);

		if (FuryWukongAnimAsset.Succeeded())
			m_FuryWukongMesh->SetAnimInstanceClass(WukongAnimAsset.Class);

	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_AttackA.AM_AttackA'"));

	if (Attack1Asset.Succeeded())
	{
		m_AttackMontage = Attack1Asset.Object;
		m_AttackMontageArray.Add(Attack1Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SkyAttackAsset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_SkyAttack.AM_SkyAttack'"));

	if (SkyAttackAsset.Succeeded())
	{
		m_SkyAttackMontage = SkyAttackAsset.Object;
		m_SkyAttackMontageArray.Add(SkyAttackAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	FuryAttackAsset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_FurryAttack.AM_FurryAttack'"));

	if (FuryAttackAsset.Succeeded())
		m_AttackMontageArray.Add(FuryAttackAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	FurySkyAttackAsset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_SkyAttack_Fury.AM_SkyAttack_Fury'"));

	if (FurySkyAttackAsset.Succeeded())
		m_SkyAttackMontageArray.Add(FurySkyAttackAsset.Object);


	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_Lighteningbolt.AM_Lighteningbolt'"));

	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill2Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_Fury.AM_Fury'"));

	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill2Asset.Object);

	m_FuryAuraEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Aura"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_aura_fire.P_ky_aura_fire'"));
	if (AuraAsset.Succeeded())
		m_FuryAuraEffect->SetTemplate(AuraAsset.Object);
	m_FuryAuraEffect->SetupAttachment(GetMesh());
	m_FuryAuraEffect->SetVisibility(false);

	m_FuryWukongMesh->SetupAttachment(GetCapsuleComponent());
	m_FuryWukongMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	m_FuryWukongMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	m_FuryWukongMesh->SetVisibility(false);
	m_FuryWukongMesh->bReceivesDecals = false;

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
	m_FuryMode = false;
	m_FuryBombCnt = 0;
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

void AWukong::Attack()
{
	if (m_OnSkillBolt)
	{
		m_BoltImpactPoint = m_BoltDecal->GetActorLocation();
		m_BoltDecal->SetSkillOn(false);
		m_BoltDecal->Destroy();
		m_BoltDecal = nullptr;
		m_OnSkillBolt = false;
		m_ActiveWidget = false;
		GetWorld()->GetTimerManager().SetTimer(m_BoltTimerHandler,
			this, &AWukong::LighteningBolt, 0.1f, true, 0.f);
		m_BoltCnt = 0;
		//if (!m_AnimInst->Montage_IsPlaying(m_Skill3FireMontage))
		//{
		//	m_AnimInst->Montage_SetPosition(m_Skill3FireMontage, 0.f);
		//	m_AnimInst->Montage_Play(m_Skill3FireMontage);

		//	//Ghost Trail On
		//	OnGhostTrail();
		//}
	}
	if (!m_ActiveWidget)
	{
		if (m_AnimInst->GetCanAttack())
		{
			//LOG(TEXT("C"));

			if (!m_AnimInst->GetOnSky())			//하늘에 있으면 땅에서 하는 콤보 공격 불가
			{
				if (GetCurrentCombo() == 0)
					m_AnimInst->Montage_Play(m_AttackMontage);
				else
					m_AnimInst->Montage_JumpToSection(m_AnimInst->GetAttackMontageSectionName(GetCurrentCombo() + 1 % 5));


				SetCurrentCombo(GetCurrentCombo() + 1);

				m_AnimInst->SetCanAttack(false);
			}
			else
			{

				//LOG(TEXT("SKY ATTACK"));
				if (!m_AnimInst->GetDoubleJump())
				{
					m_AnimInst->Montage_Play(m_SkyAttackMontage);
				}

				m_AnimInst->SetCanAttack(false);
			}
		}

	}
}
void AWukong::HitDamage()
{
	Super::HitDamage();

	if (!m_FuryMode)
	{
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
		//FColor DrawColor = CollisionArray.Num() > 0 ? FColor::Red : FColor::Green;
		//DrawDebugCone(GetWorld(), PlayerLoc, GetActorForwardVector(), m_PlayerInfo.AttackDistance, FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), FMath::DegreesToRadians(m_PlayerInfo.AttackAngle), 20, DrawColor, false, 1.f);
		////DrawDebugSphere(GetWorld(), PlayerLoc, m_PlayerInfo.AttackDistance, 20, DrawColor, false, 1.f);
#endif
		m_LaunchPower = 1.0f;
		for (auto& result : CollisionArray)
		{
			if (m_ActiveComboTime)
			{
				m_ComboCnt++;
				GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
				GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APlayerCharacter::ResetCombo, 2.f, false, -1.f);
			}
			else
			{
				m_ComboCnt = 1;
				GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APlayerCharacter::ResetCombo, 2.f, false, -1.f);
				m_ActiveComboTime = true;
			}

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			/*	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
					result.ImpactPoint, result.ImpactNormal.Rotation(), param);*/


			UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
			ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(result.ImpactPoint, result.ImpactNormal.Rotation(), ANormalEffect::StaticClass()));
			if (Effect != nullptr)
			{
				if (m_FuryMode != true)
					Effect->LoadParticleAsync(TEXT("HitFire"));
				else
					Effect->LoadParticleAsync(TEXT("Saga_Impact"));
			}

			//에셋 로딩
			//Effect->LoadParticle(TEXT("ParticleSystem'/Game/ParagonSunWukong/FX/Particles/Wukong/Abilities/Primary/FX/P_Wukong_Impact_Empowered.P_Wukong_Impact_Empowered'"));
			//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));

			//Effect->LoadSoundAsync(TEXT("HitNormal"));
			//데미지 전달
			FDamageEvent DmgEvent;
			float CriticalRandom = FMath::RandRange(0.f, 100.f);
			if (CriticalRandom <= m_PlayerInfo.CriticalPercent)
				m_IsCritical = true;

			else
				m_IsCritical = false;

			int PlayerLevel = m_PlayerInfo.Level;
			int DamageRandom = FMath::RandRange(-5 * PlayerLevel, 5 * PlayerLevel);
			int FuryDamage = m_FuryMode ? 2 : 1;
			float Damage = result.GetActor()->TakeDamage(((20 + DamageRandom) * GetPlayerInfo().CriticalDamage) * FuryDamage, DmgEvent, GetController(), this);
		}
	}
	else
	{
		FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));

		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		AWukongAttackProjectile* Bullet = Cast<AWukongAttackProjectile>(GameInst->GetParticlePool()->Pop(MuzzleLoc, GetActorRotation(), AWukongAttackProjectile::StaticClass()));

		if (m_ActiveComboTime)
		{
			m_ComboCnt++;
			GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APlayerCharacter::ResetCombo, 2.f, false, -1.f);
		}
		else
		{
			m_ComboCnt = 1;
			GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APlayerCharacter::ResetCombo, 2.f, false, -1.f);
			m_ActiveComboTime = true;
		}

		if (Bullet)
		{
			Bullet->SetProjectileOwner(this);
			Bullet->SetActiveBullet(GetActorForwardVector());

			int PlayerLevel = m_PlayerInfo.Level;
			int DamageRandom = FMath::RandRange(-5 * PlayerLevel, 5 * PlayerLevel);

			Bullet->SetAttack(((20 + DamageRandom) * GetPlayerInfo().CriticalDamage) * 2.f);
		}
	}
}

void AWukong::UseSkill(int32 Idx)
{
	switch (Idx)
	{
	case 0:
	{
		if (m_FuryMode)
		{
			if (m_BoltCnt != 0)
			{
				GetWorld()->GetTimerManager().SetTimer(m_BoltTimerHandler,
					this, &AWukong::FuryLighteningBolt, 0.05f, true, 0.f);
				m_BoltCnt = 0;
			}
		}
		else
		{
			if (!m_OnSkillBolt)
			{
				m_OnSkillBolt = true;
				m_ActiveWidget = true;
				FActorSpawnParameters param;

				if (m_BoltDecal == nullptr)
				{
					param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					m_BoltDecal = GetWorld()->SpawnActor<ABoltDecal>(ABoltDecal::StaticClass()
						, GetActorLocation(),
						FRotator::ZeroRotator, param);

					m_BoltDecal->SetSkillOn(true);
				}
			}
		}

		//LOG(TEXT("A"));
		//m_AnimInst->Montage_JumpToSection(TEXT("Start"), m_SkillMontageArray[0]);
	}
	break;
	
	case 1:
	{
		if (m_ComboCnt >= 5)
		{
			m_ComboCnt = 0;
			GetWorld()->GetTimerManager().SetTimer(m_FuryModeTimerHandler,
				this, &AWukong::UnSetFuryMode, 15.f, false, -1.f);
			SetFuryMode();
		}
		else
			return;
	}
	break;
	}

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

}

void AWukong::LighteningBolt()
{
	m_BoltCnt++;
	if (m_BoltCnt > 20)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_BoltTimerHandler);
		//LOG(TEXT("B"));
		m_AnimInst->Montage_JumpToSection(TEXT("End"), m_SkillMontageArray[0]);

	}
	else
	{
		FCollisionQueryParams params(NAME_None, false, this);

		TArray<FHitResult> HitResultArray;

		bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, m_BoltImpactPoint, m_BoltImpactPoint, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
			, FCollisionShape::MakeSphere(500.f), params);
		//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(UHitCameraShake::StaticClass());
		m_LaunchPower = 5.0f;
		if (Sweep)
		{
			for (auto result : HitResultArray)
			{
				//LOG(TEXT("%s"), *result.GetActor()->GetName());

					//데미지 전달
				FDamageEvent DmgEvent;
				float CriticalRandom = FMath::RandRange(0.f, 100.f);
				if (CriticalRandom <= m_PlayerInfo.CriticalPercent)
					m_IsCritical = true;
				else
					m_IsCritical = false;

				int PlayerLevel = m_PlayerInfo.Level;
				int DamageRandom = FMath::RandRange(-5 * PlayerLevel, 5 * PlayerLevel);

				int FuryDamage = m_FuryMode ? 2 : 1;
				float Damage = result.GetActor()->TakeDamage(((50 + DamageRandom) * GetPlayerInfo().CriticalDamage) * FuryDamage, DmgEvent, GetController(), this);

			}
		}

		float RandomX = FMath::RandRange(-200.f, 200.f);
		float RandomY = FMath::RandRange(-200.f, 200.f);

		if (m_FuryMode == false)
		{
			UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
			ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(m_BoltImpactPoint + FVector(RandomX, RandomY, 0), GetActorRotation(), ANormalEffect::StaticClass()));
			if (Effect != nullptr)
				Effect->LoadParticleAsync(TEXT("Player_Bolt"));

		}
	}
}

void AWukong::FuryLighteningBolt()
{
	m_BoltCnt++;
	if (m_BoltCnt > 100)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_BoltTimerHandler);
		//LOG(TEXT("B"));
		m_AnimInst->Montage_JumpToSection(TEXT("End"), m_SkillMontageArray[0]);
		(GetMesh()->GetAnimInstance())->Montage_JumpToSection(TEXT("End"), m_SkillMontageArray[0]);
	}
	else
	{
		FCollisionQueryParams params(NAME_None, false, this);

		TArray<FHitResult> HitResultArray;

		bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
			, FCollisionShape::MakeSphere(5000.f), params);
		//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(UHitCameraShake::StaticClass());
		m_LaunchPower = 5.0f;
		if (Sweep)
		{
			for (auto result : HitResultArray)
			{
				//LOG(TEXT("%s"), *result.GetActor()->GetName());

					//데미지 전달
				FDamageEvent DmgEvent;
				float CriticalRandom = FMath::RandRange(0.f, 100.f);
				if (CriticalRandom <= m_PlayerInfo.CriticalPercent)
					m_IsCritical = true;
				else
					m_IsCritical = false;

				int PlayerLevel = m_PlayerInfo.Level;
				int DamageRandom = FMath::RandRange(-5 * PlayerLevel, 5 * PlayerLevel);

				int FuryDamage = m_FuryMode ? 2 : 1;
				float Damage = result.GetActor()->TakeDamage(((50 + DamageRandom) * GetPlayerInfo().CriticalDamage) * FuryDamage, DmgEvent, GetController(), this);
			}
		}
	

		float RandomX = FMath::RandRange(-1000.f, 1000.f);
		float RandomY = FMath::RandRange(-1000.f, 1000.f);

		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(GetActorLocation() + FVector(RandomX, RandomY, 0), GetActorRotation(), ANormalEffect::StaticClass()));
		if (Effect != nullptr)
			Effect->LoadParticleAsync(TEXT("Saga_Bolt"));

	}
}


void AWukong::SetFuryMode()
{
	if (!m_FuryMode)
	{
		m_AttackMontage = m_AttackMontageArray[1];
		m_SkyAttackMontage = m_SkyAttackMontageArray[1];
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(GetActorLocation() - FVector(0.f, 0.f, 90.f), GetActorRotation(), ANormalEffect::StaticClass()));
		if (Effect != nullptr)
			Effect->LoadParticleAsync(TEXT("Saga_Start"));

		ANormalEffect* Effect1 = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(GetActorLocation() - FVector(0.f, 0.f, 90.f), GetActorRotation(), ANormalEffect::StaticClass()));
		if (Effect1 != nullptr)
			Effect1->LoadParticleAsync(TEXT("Saga_Destroy"));
		//m_FuryAuraEffect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(GetActorLocation() - FVector(0.f, 0.f, 90.f), GetActorRotation(), ANormalEffect::StaticClass()));
		
		m_FuryAuraEffect->SetVisibility(true);
	
		m_FuryWukongMesh->SetVisibility(true);
		GetMesh()->SetVisibility(false);
		m_AnimInst = Cast<UPlayerAnim>(m_FuryWukongMesh->GetAnimInstance());
		m_FuryMode = true;
	}
	else
	{
		if (m_FuryBombCnt < 1)
		{
			FCollisionQueryParams params(NAME_None, false, this);

			TArray<FHitResult> HitResultArray;
			bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
				, FCollisionShape::MakeSphere(3000.f), params);
			//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(UHitCameraShake::StaticClass());
			m_IsCritical = false;
			m_LaunchPower = 5.0f;
			if (Sweep)
			{
				for (auto result : HitResultArray)
				{

					//데미지 전달
					FDamageEvent DmgEvent;
					float Damage = result.GetActor()->TakeDamage(2000, DmgEvent, GetController(), this);

				}
			}
		}
	}
}
void AWukong::UnSetFuryMode()
{
	if (m_FuryMode)
	{
		m_AttackMontage = m_AttackMontageArray[0];
		m_SkyAttackMontage = m_SkyAttackMontageArray[0];

		m_FuryWukongMesh->SetVisibility(false);
		GetMesh()->SetVisibility(true);

		bool CanAttack = m_AnimInst->GetCanAttack();

		m_AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
		m_AnimInst->SetCanAttack(true);
		
		m_FuryAuraEffect->SetVisibility(false);
		
		m_AnimInst->SetCanAttack(true);
		//LOG(TEXT("END"));
		
		m_FuryMode = false;
		m_FuryBombCnt = 0;
	}
}

bool AWukong::SkillPlayAnim(int32 idx)
{
	bool result = Super::SkillPlayAnim(idx);

	if (result)
	{
		if (!m_FuryMode)
		{
			(Cast<UPlayerAnim>(m_FuryWukongMesh->GetAnimInstance())->Montage_SetPosition(m_SkillMontageArray[idx], 0.f));
			(Cast<UPlayerAnim>(m_FuryWukongMesh->GetAnimInstance())->Montage_Play((m_SkillMontageArray[idx])));
		}
		else
		{
			(Cast<UPlayerAnim>(GetMesh()->GetAnimInstance())->Montage_SetPosition(m_SkillMontageArray[idx], 0.f));
			(Cast<UPlayerAnim>(GetMesh()->GetAnimInstance())->Montage_Play((m_SkillMontageArray[idx])));
		}
		return true;
	}

	return false;
}

void AWukong::SlamDamage()
{
	SetTimeDillation();
	GetCharacterMovement()->GravityScale = 1.0f;

	m_AnimInst->SetCanAttack(true);

	FCollisionQueryParams params(NAME_None, false, this);

	TArray<FHitResult> HitResultArray;
	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
		, FCollisionShape::MakeSphere(500.f), params);
	//LOG(TEXT("%f"), MonsterInfo.TraceDistance);

#if ENABLE_DRAW_DEBUG
	/*	FColor DrawColor = Sweep ? FColor::Red : FColor::Green;

		DrawDebugSphere(GetWorld(), GetActorLocation(), 500, 20, DrawColor, false
			, 0.3f);*/

#endif
	FVector impactPoint = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 80.f);


	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			impactPoint, FRotator::ZeroRotator, param);
		Effect->LoadParticleAsync(TEXT("Slam1"));*/

	if (m_FuryMode == false)
	{
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator, ANormalEffect::StaticClass()));

		Effect->LoadParticleAsync(TEXT("Slam2"));

		ANormalEffect* Effect1 = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator, ANormalEffect::StaticClass()));
		Effect1->LoadParticleAsync(TEXT("Slam3"));
	}
	else
	{
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator, ANormalEffect::StaticClass()));

		Effect->LoadParticleAsync(TEXT("Saga_Slam2"));

		ANormalEffect* Effect1 = Cast<ANormalEffect>(GameInst->GetParticlePool()->Pop(impactPoint, FRotator::ZeroRotator, ANormalEffect::StaticClass()));
		Effect1->LoadParticleAsync(TEXT("Saga_Slam3"));
	}
	SetLaunchPower(1.0f);
	if (Sweep)
	{
		for (auto result : HitResultArray)
		{

			//데미지 전달
			FDamageEvent DmgEvent;
			float CriticalRandom = FMath::RandRange(0.f, 100.f);

			if (CriticalRandom <= GetPlayerInfo().CriticalPercent)
				SetCritical(true);
			else
				SetCritical(false);

			int PlayerLevel = GetPlayerInfo().Level;
			int DamageRandom = FMath::RandRange(-5 * PlayerLevel, 5 * PlayerLevel);

			int FuryDamage = m_FuryMode ? 2 : 1;
			float Damage = result.GetActor()->TakeDamage(((150 + DamageRandom) * GetPlayerInfo().CriticalDamage) * FuryDamage, DmgEvent, GetController(), this);

		}
	}


}
void AWukong::SetCanAttack()
{
	Cast<UPlayerAnim>(GetMesh()->GetAnimInstance())->SetCanAttack(true);
}
