// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"
#include "../DebugClass.h"
ACustomCharacter::ACustomCharacter()
{
	m_Active = false;
}

ACustomCharacter::~ACustomCharacter()
{
	//LOG(TEXT("CHAR DEL"));
}
// Sets default values
void ACustomCharacter::SetActive(bool bOnFlag)
{
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
bool ACustomCharacter::GetActive()
{
	if (this == nullptr)
		return true;

	return m_Active;
}