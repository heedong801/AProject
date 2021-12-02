// Fill out your copyright notice in the Description page of Project Settings.


#include "Nexus.h"
#include "../UI/HPBar.h"
#include "../DebugClass.h"
// Sets default values
ANexus::ANexus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	m_HPBar->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FClassFinder<UUserWidget>	HPBarAsset(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));

	if (HPBarAsset.Succeeded())
		m_HPBar->SetWidgetClass(HPBarAsset.Class);

	m_HPBar->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBar->SetDrawSize(FVector2D(200.f, 60.f));
	m_HPBar->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	m_HPBar->SetBlendMode(EWidgetBlendMode::Transparent);

	MaxHp = 500;
	Hp = 50;

}

// Called when the game starts or when spawned
void ANexus::BeginPlay()
{
	Super::BeginPlay();
	
	m_HPBarWidget = Cast<UHPBar>(m_HPBar->GetWidget());

	m_HPBarWidget->SetName(TEXT("Nexus"));
}

// Called every frame
void ANexus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ANexus::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;

	if (m_HPBarWidget->GetVisibility() == ESlateVisibility::Collapsed)
		m_HPBarWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Damage = Damage < 1.f ? 1.f : Damage;
	LOG(TEXT("HIT"));
	Hp -= Damage;

	//죽은경우
	if (Hp <= 0)
	{
		LOG(TEXT("LOSE"));

		
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


	if (IsValid(m_HPBarWidget))
	{
		m_HPBarWidget->SetHPPercent(Hp/MaxHp);
	}
	return Damage;
}