// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "SubLevelTrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ASubLevelTrigger : public ABoxTrigger
{
	GENERATED_BODY()
	
public:
	ASubLevelTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_StreamingLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_ExceptStreamingLevelName;
protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION()
		void TriggerBegin();

	UFUNCTION()
		void TriggerEnd();
};
