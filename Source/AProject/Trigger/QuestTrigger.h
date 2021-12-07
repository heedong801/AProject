// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "QuestTrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AQuestTrigger : public ABoxTrigger
{
	GENERATED_BODY()

private:
	bool m_Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_QuestStr;
public:
	AQuestTrigger();

protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION()
		void TriggerBegin();
};
