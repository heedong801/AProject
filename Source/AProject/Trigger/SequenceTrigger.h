// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "SequenceTrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ASequenceTrigger : public ABoxTrigger
{
	GENERATED_BODY()
public:
	ASequenceTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ULevelSequence* m_SequenceAsset;

	ULevelSequencePlayer* m_SequencePlayer;
	ALevelSequenceActor* m_SequenceActor;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void TriggerBegin();

};

