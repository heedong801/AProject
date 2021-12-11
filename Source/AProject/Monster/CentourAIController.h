// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "CentourAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ACentourAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ACentourAIController();

protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
