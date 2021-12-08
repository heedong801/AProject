// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "BlueFlyAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ABlueFlyAIController : public AMonsterAIController
{
	GENERATED_BODY()

public:
	ABlueFlyAIController();
protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
