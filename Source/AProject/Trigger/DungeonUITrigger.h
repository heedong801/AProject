// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxTrigger.h"
#include "DungeonUITrigger.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API ADungeonUITrigger : public ABoxTrigger
{
	GENERATED_BODY()
public:
	ADungeonUITrigger();

public:
	UFUNCTION()
		void TriggerBegin();

	UFUNCTION()
		void TriggerEnd();

	void Interaction();

};
