// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "GolemAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AGolemAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	AGolemAIController();

protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
