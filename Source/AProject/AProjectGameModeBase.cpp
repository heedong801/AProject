 // Copyright Epic Games, Inc. All Rights Reserved.


#include "AProjectGameModeBase.h"
#include "AProjectGameInstance.h"
#include "Player/PlayerCharacter.h"
#include "DebugClass.h"

AAProjectGameModeBase::AAProjectGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UMainHUD>	MainHUDClass(TEXT("WidgetBlueprint'/Game/UI/UI_MainHUD.UI_MainHUD_C'"));

	if (MainHUDClass.Succeeded())
		m_MainHUDClass = MainHUDClass.Class;

	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Wukong/BP_Wukong.BP_Wukong_C'"));
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;

	m_ParticlePool = CreateDefaultSubobject<UParticlePool>(TEXT("ParticlePool"));
	m_CharacterPool = CreateDefaultSubobject<UCharacterPool>(TEXT("CharacterPool"));

}

void AAProjectGameModeBase::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		EPlayerJob SelectJob = GameInst->GetSelectJob();

		switch (SelectJob)
		{
		case EPlayerJob::Knight:
		{
			DefaultPawnClass = m_PlayerClassArray[0];
		}
		break;
		case EPlayerJob::Archer:
		{
			DefaultPawnClass = m_PlayerClassArray[1];
		}
		break;
		case EPlayerJob::Magicion:
		{
			DefaultPawnClass = m_PlayerClassArray[2];
		}
		break;
		}
	}*/
	//m_CharacterPool = CreateDefaultSubobject<UCharacterPool>(TEXT("CharacterPool"));
	m_ParticlePool->MakePool();
	m_CharacterPool->MakePool();

	m_MainAssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();

	m_MainAssetPath->ConvertPath();
}
void AAProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//m_CharacterPool = NewObject<UCharacterPool>(GetWorld(), UCharacterPool::StaticClass(), TEXT("CharacterPool"));

	if (IsValid(m_MainHUDClass))
	{
		m_MainHUD = Cast<UMainHUD>(CreateWidget(GetWorld(),
			m_MainHUDClass));

		if (m_MainHUD)
			m_MainHUD->AddToViewport();
	}

	
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = false;
}

void AAProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


UParticlePool* AAProjectGameModeBase::GetParticlePool()
{
	if (IsValid(m_ParticlePool))
		return m_ParticlePool;
	else
		return nullptr;
}

UCharacterPool* AAProjectGameModeBase::GetCharacterPool()
{
	if (IsValid(m_CharacterPool))
		return m_CharacterPool;
	else
		return nullptr;
}

