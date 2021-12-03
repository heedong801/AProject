// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "SpawnTrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ASpawnTrigger : public ABoxTrigger
{
	GENERATED_BODY()

public:
	ASpawnTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class AMonsterSpawnPoint*> m_SpawnPointArray;

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TriggerBegin();

};
