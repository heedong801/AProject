// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "../UI/HPBar.h"
#include "../DebugClass.h"
#include "../AProjectGameModeBase.h"
#include "../AProjectGameModeBase.h"
#include "../Player/PlayerCharacter.h"
#include "../Monster/Monster.h"
// Sets default values
ANexus::ANexus()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));

	m_Top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	m_Mid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mid"));
	m_Bottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));

	m_Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));

	SetRootComponent(m_Body);
	m_Top->SetupAttachment(m_Body);
	m_Mid->SetupAttachment(m_Body);
	m_Bottom->SetupAttachment(m_Body);
	m_HPBar->SetupAttachment(m_Body);

	m_FirstDamagedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FirstPoint"));
	m_SecondDamagedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SecondPoint"));
	m_ThirdDamagedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	static ConstructorHelpers::FClassFinder<UUserWidget>	HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));

	if (HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f, 60.f));
	m_HPBar->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);
	//m_HPBar->SetTintColorAndOpacity(FLinearColor(0.0f, 1.f, 1.f, 0.8f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("ParticleSystem'/Game/ParagonProps/FX/Particles/Turret/P_SentryTurret_Dmg_ForNexus.P_SentryTurret_Dmg_ForNexus'"));

	m_FirstDamagedParticle->SetupAttachment(m_Body);
	m_SecondDamagedParticle->SetupAttachment(m_Body);
	m_ThirdDamagedParticle->SetupAttachment(m_Body);

	if (Asset.Succeeded())
	{
		m_FirstDamagedParticle->SetTemplate(Asset.Object);
		m_SecondDamagedParticle->SetTemplate(Asset.Object);
		m_ThirdDamagedParticle->SetTemplate(Asset.Object);
	}

	Hp = 2000;
	IsExployed = false;
	m_Top->bReceivesDecals = false;
	m_Mid->bReceivesDecals = false;
	m_Bottom->bReceivesDecals = false;

}

// Called when the game starts or when spawned
void ANexus::BeginPlay()
{
	Super::BeginPlay();
	
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());
	//m_HPBarWidget->GetHPBar()->SetFillColorAndOpacity(FLinearColor(1.0f, 1.f, 0.f, 0.8f));
	m_HPBarWidget->SetName(TEXT("Nexus"));

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	//LOG(TEXT("%f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//LOG(TEXT("%f %f %f"), m_Bottom->GetRelativeLocation().X, m_Bottom->GetRelativeLocation().Y, m_Bottom->GetRelativeLocation().Z);
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	m_Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(GetActorLocation() + FVector(0.f, 0.f, -260.f), FRotator::ZeroRotator, ANormalEffect::StaticClass()));
	if (m_Effect)
	{
		m_Effect->SetActorScale3D(FVector(1.f, 2.f, 1.f));
		m_Effect->LoadParticleAsync(TEXT("Nexus"));
	}
	m_FirstDamagedParticle->SetVisibility(false);
	m_SecondDamagedParticle->SetVisibility(false);
	m_ThirdDamagedParticle->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(m_ClearTimer, this, 
		&ANexus::CheckClear, 30.f, false, -1.f);

}

void ANexus::CheckClear() 
{
	if (Hp > 0)
	{
		if (m_SequenceAsset)
		{
			// ???? ?????? ?????????? ?????? ??????????.
			if (!m_SequencePlayer)
			{
				m_SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
					GetWorld(), m_SequenceAsset, FMovieSceneSequencePlaybackSettings(),
					m_SequenceActor);
			}

			m_SequencePlayer->Play();

			//PrintViewport(1.f, FColor::Red, TEXT("SequencePlay"));
		}

		/*TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), Actors);

		for (AActor* Actor : Actors)
		{
			AMonster* Monster = Cast<AMonster>(Actor);
			if (Monster)
			{
				FVector MonsterLoc = Monster->GetActorLocation();
				float Distance = FVector::Distance(MonsterLoc, GetActorLocation());

				if (Distance <= 1500.f)
					Monster->Destroy();
			}
		}*/
		//// ???????? ?????? ???? ???????? ???? ???????? ???? ???????? ?????? ????????.
		AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();
			if (QuestWidget)
			{
				QuestWidget->QuestCheck(EQuestType::Defense, TEXT("Nexus"));
			}
		}

		m_HPBarWidget->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetTimerManager().SetTimer(m_RecallTimer, this,
			&ANexus::RecallEffectAfterSequence, 2.25f, false);

		/*APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();

		ANormalEffect* Effect1 = GameInst->GetParticlePool()->Pop(Player->GetActorLocation(), GetActorRotation());
		if (Effect1)
			Effect1->LoadParticleAsync(TEXT("Player_Recall"));*/

	}
}

void ANexus::RecallEffectAfterSequence()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(GetActorLocation() + FVector(0.f, 0.f, -130.f), GetActorRotation(), ANormalEffect::StaticClass()));
	if (Effect)
		Effect->LoadParticleAsync(TEXT("Nexus_MagicCircle"));

	GetWorld()->GetTimerManager().SetTimer(m_RecallTimer, this,
		&ANexus::Recall, 0.5f, false);
}
void ANexus::PlayerRecall()
{
	APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	ANormalEffect* Effect1 = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(m_NextPosition , Player->GetActorRotation(), ANormalEffect::StaticClass()));
	if (Effect1)
	{
		Effect1->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
		Effect1->LoadParticleAsync(TEXT("Player_Recall"));
		Player->SetActorLocation(m_NextPosition);

	}
}
void ANexus::Recall()
{

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	ANormalEffect* Effect1 = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(GetActorLocation(), GetActorRotation(), ANormalEffect::StaticClass()));
	if (Effect1)
	{
		Effect1->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
		Effect1->LoadParticleAsync(TEXT("Player_Recall"));

		GetWorld()->GetTimerManager().SetTimer(m_PlayerRecallTimer, this,
			&ANexus::PlayerRecall, 1.25f, false);
		/*APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
		Player->SetActorLocation(m_NextPosition);*/
		FLatentActionInfo	Info;

		if (m_NextStreamingLevelName.Len() != 0)
		{
			UGameplayStatics::LoadStreamLevel(GetWorld(), *m_NextStreamingLevelName,
				true, false, Info);

		}
	}
}
// Called every frame
void ANexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsExployed)
		m_Top->AddRelativeRotation(FRotator(0.f, 0.5f, 0.f));
}

void ANexus::Exploy(FVector HitPos, FRotator NormalRot)
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(HitPos, NormalRot, ANormalEffect::StaticClass()));
	Effect->LoadParticleAsync(TEXT("Nexus_Exploy"));
	m_ExployCnt++;
	if (m_ExployCnt == 6)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_ExployedTimer);
		
		Destroy();
	}
}

float ANexus::TakeDamageForNexus(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FVector HitPos, FRotator NormalRot)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;

	if (m_HPBarWidget->GetVisibility() == ESlateVisibility::Collapsed)
		m_HPBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Damage = Damage < 1.f ? 1.f : Damage;
	
	Hp -= Damage;


	//LOG(TEXT("HIT"));
	//????????
	if (Hp <= 0)
	{
		IsExployed = true;
		//m_Effect->SetLifeSpan(0.1f);
		m_FirstDamagedParticle->SetVisibility(false);
		m_SecondDamagedParticle->SetVisibility(false);
		m_ThirdDamagedParticle->SetVisibility(false);

		//Effect->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	
		m_TimerDelegate.BindUFunction(this, FName("Exploy"), HitPos, NormalRot);
		GetWorld()->GetTimerManager().SetTimer(m_ExployedTimer,
			 m_TimerDelegate, 0.5f, true, 0.f );

		FHitResult HitResult;
		TArray<FHitResult> HitResultArray;

		bool Sweep = false;
		FCollisionQueryParams params(NAME_None, false, this);

		Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3
				, FCollisionShape::MakeSphere(3500.f), params);

		for (auto result : HitResultArray)
		{
			if (Sweep)
			{
				//ANormalEffect* Effect3 = GameInst->GetParticlePool()->Pop(result.ImpactPoint, result.ImpactNormal.Rotation());

				//???? ????
				//Effect3->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_impact.P_ky_impact'"));
				//Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));
				//Effect3->LoadParticleAsync(TEXT("HitNormal"));
				//Effect->LoadSoundAsync(TEXT("HitNormal"));

				//?????? ????
				FDamageEvent DmgEvent;
				result.GetActor()->TakeDamage(1500, DmgEvent, nullptr, this);
			}
		}
		
	}
	else
	{
		AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

		ANormalEffect* Effect = Cast<ANormalEffect>(GameMode->GetParticlePool()->Pop(HitPos, NormalRot, ANormalEffect::StaticClass()));
		Effect->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		Effect->LoadParticleAsync(TEXT("Nexus_Shield"));

		float perHp = Hp / (float)MaxHp * 100;
		//LOG(TEXT("%f"), perHp);
		if (perHp <= 30)
			m_ThirdDamagedParticle->SetVisibility(true);
		else if (perHp <= 60)
			m_SecondDamagedParticle->SetVisibility(true);
		else if (perHp <= 90)
			m_FirstDamagedParticle->SetVisibility(true);
	}

	if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(Hp/(float)MaxHp);
	}
	return Damage;
}