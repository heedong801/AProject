// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "../UI/HPBar.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
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

	MaxHp = 500;
	Hp = 500;
	IsExployed = false;
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

	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
	//LOG(TEXT("%f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//LOG(TEXT("%f %f %f"), m_Bottom->GetRelativeLocation().X, m_Bottom->GetRelativeLocation().Y, m_Bottom->GetRelativeLocation().Z);

	m_Effect = GameInst->GetParticlePool()->Pop(GetActorLocation() + FVector(0.f, 0.f, -260.f), FRotator::ZeroRotator);
	m_Effect->SetActorScale3D(FVector(1.f, 2.f, 1.f));
	m_Effect->LoadParticleAsync(TEXT("Nexus"));

	m_FirstDamagedParticle->SetVisibility(false);
	m_SecondDamagedParticle->SetVisibility(false);
	m_ThirdDamagedParticle->SetVisibility(false);
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
	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
	ANormalEffect* Effect = GameInst->GetParticlePool()->Pop(HitPos, NormalRot);
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
	//죽은경우
	if (Hp <= 0)
	{
		IsExployed = true;
		m_Effect->SetLifeSpan(0.1f);
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
				, FCollisionShape::MakeSphere(500.f), params);

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
				result.GetActor()->TakeDamage(500, DmgEvent, nullptr, this);
			}
		}
		//// 몬스터가 죽었을 경우 퀘스트에 해당 몬스터를 잡는 퀘스트가 있는지 판단한다.
		//AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

		//if (GameMode)
		//{

		//	UQuestWidget* QuestWidget = GameMode->GetMainHUD()->GetQuestWidget();

		//	if (QuestWidget)
		//	{

		//		QuestWidget->QuestCheck(EQuestType::Hunt, m_MonsterInfo.Name);
		//	}
	}
	else
	{
		UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());
		ANormalEffect* Effect = GameInst->GetParticlePool()->Pop(HitPos, NormalRot);
		Effect->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
		Effect->LoadParticleAsync(TEXT("Nexus_Shield"));

		float perHp = Hp / (float)MaxHp * 100;
		LOG(TEXT("%f"), perHp);
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