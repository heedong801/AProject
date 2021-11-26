// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAIController.h"
#include "ShoebillAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AShoebillAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AShoebillAIController();

protected:

	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
