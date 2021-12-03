// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomActor.generated.h"

UCLASS()
class APROJECT_API ACustomActor : public AActor
{
	GENERATED_BODY()
	
private:
	bool m_Active;
public:	
	// Sets default values for this actor's properties
	ACustomActor();

	void SetActive(bool bOnFlag);
	bool GetActive();

};
