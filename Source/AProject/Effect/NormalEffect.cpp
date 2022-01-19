// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEffect.h"
#include "../AssetManager/AssetPathMain.h"
#include "../DebugClass.h"
// Sets default values
ANormalEffect::ANormalEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	SetRootComponent(m_ParticleSystem);

	m_AssetLoop = false;

}

// Called when the game starts or when spawned
void ANormalEffect::BeginPlay()
{
	Super::BeginPlay();

	if (!m_AssetLoop)
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormalEffect::LoadParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, *Path);

	if (Particle)
	{

		m_ParticleSystem->SetTemplate(Particle);
	}
}

void ANormalEffect::LoadSound(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if (Sound)
	{

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
	}
}

void ANormalEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	SetActorScale3D(FVector(1.f, 1.f, 1.f));
	m_ParticleSystem->SetVisibility(false);
	SetActive(false);
}

void ANormalEffect::LoadSoundAsync(const FString& Name)
{
	UAssetPathMain* AssetPath = UAssetPathMain::StaticClass()->GetDefaultObject< UAssetPathMain>();

	const FSoftObjectPath* Path = AssetPath->FindSoundPath(Name);

	if (!Path)
		return;

	m_AsyncSoundPath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncSoundLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncSoundPath,
		FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadSoundAsyncComplete));

}
void ANormalEffect::LoadParticleAsync(const FString& Name)
{
	UAssetPathMain* AssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();
	
	const FSoftObjectPath* Path = AssetPath->FindParticlePath(Name);

	if (!Path)
		return;


	m_AsyncParticlePath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath,
		FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadParticleAsyncComplete));

}


void ANormalEffect::LoadParticleAsyncComplete()
{
	TAssetPtr<UParticleSystem> NewParticle(m_AsyncParticlePath);

	if (NewParticle)
	{
		m_ParticleSystem->SetTemplate(NewParticle.Get());
		//m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);

	}
	m_AsyncParticleLoadHandle->ReleaseHandle();
}
void ANormalEffect::LoadSoundAsyncComplete()
{

	TAssetPtr<USoundBase> NewSound(m_AsyncSoundPath);

	if (NewSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NewSound.Get(), GetActorLocation());

	m_AsyncSoundLoadHandle->ReleaseHandle();
}

void ANormalEffect::SetObject()
{
	m_ParticleSystem->SetVisibility(true);
}

void ANormalEffect::SetActive(bool bOnActive)
{
	Super::SetActive(bOnActive);

	m_ParticleSystem->SetVisibility(true);
}
