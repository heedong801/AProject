// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "Engine/EngineTypes.h"
#include "LevelTrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ALevelTrigger : public ABoxTrigger
{
	GENERATED_BODY()

public:
	ALevelTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_StreamingLevelName;

	FTimerHandle m_MapLoadTimer;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void TriggerBegin();

	UFUNCTION()
		void TriggerEnd();
	UFUNCTION()
		void LoadMap();

};
