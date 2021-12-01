// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MainHUD.h"
#include "GameFramework/GameModeBase.h"
#include "AssetManager/AssetPathMain.h"
#include "Effect/ParticlePool.h"
#include "AProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAProjectGameModeBase();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UMainHUD>	m_MainHUDClass;

	UMainHUD* m_MainHUD;

	UAssetPathMain* m_MainAssetPath;
	
	UParticlePool* m_ParticlePool;
public:
	UMainHUD* GetMainHUD()	{		return m_MainHUD;	}

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
