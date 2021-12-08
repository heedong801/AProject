// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceTrigger.h"




// Sets default values
ASequenceTrigger::ASequenceTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SequenceAsset = nullptr;
	m_SequencePlayer = nullptr;
}

void ASequenceTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ASequenceTrigger::TriggerBegin);
	//m_TriggerEndDelegate.AddDynamic(this, &ASequenceTrigger::TriggerEnd);
}

// Called every frame
void ASequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASequenceTrigger::TriggerBegin()
{
	if (m_SequenceAsset)
	{
		// 만약 시퀀스 플레이어가 없다면 생성해준다.
		if (!m_SequencePlayer)
		{
			m_SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), m_SequenceAsset, FMovieSceneSequencePlaybackSettings(),
				m_SequenceActor);
		}

		m_SequencePlayer->Play();

		//PrintViewport(1.f, FColor::Red, TEXT("SequencePlay"));
	}
}



