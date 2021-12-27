// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

UCLASS()
class APROJECT_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool m_Active;
public:
	// Sets default values for this actor's properties
	ACustomCharacter();
	~ACustomCharacter();

	virtual void SetActive(bool bOnFlag);
	virtual bool GetActive();

};
