// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "BarghestAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ABarghestAIController : public AMonsterAIController
{
	GENERATED_BODY()

public:
	ABarghestAIController();
protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
