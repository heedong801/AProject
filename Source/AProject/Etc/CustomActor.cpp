// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomActor.h"
#include "../DebugClass.h"
ACustomActor::ACustomActor()
{
	m_Active = false;
}

ACustomActor::~ACustomActor()
{
	LOG(TEXT("ACTOR DEL"));
}

// Sets default values
void ACustomActor::SetActive(bool bOnFlag)
{
	LOG(TEXT("ACustomActor SetActive"));

	m_Active = bOnFlag;
	if (bOnFlag)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}
bool ACustomActor::GetActive()
{
	if (this == nullptr || !IsValid(this))
		return true;

	return m_Active;
}
