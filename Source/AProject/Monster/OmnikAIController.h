// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "OmnikAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AOmnikAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AOmnikAIController();

protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
