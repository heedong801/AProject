// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/AssetManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NormalEffect.generated.h"

UCLASS()
class APROJECT_API ANormalEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_ParticleSystem;

	FSoftObjectPath		m_AsyncParticlePath;
	FSoftObjectPath		m_AsyncSoundPath;

	TSharedPtr<FStreamableHandle>	m_AsyncParticleLoadHandle;
	TSharedPtr<FStreamableHandle>	m_AsyncSoundLoadHandle;


	bool m_AssetLoop;

public:
	void AssetLoop()
	{
		m_AssetLoop = true;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LoadParticle(const FString& Path);
	void LoadSound(const FString& Path);
	void LoadSoundAsync(const FString& Name);
	void LoadParticleAsync(const FString& Name);
	void LoadParticleAsyncComplete();
	void LoadSoundAsyncComplete();

	UFUNCTION()
	void ParticleFinish(UParticleSystemComponent* Particle);
	
};
