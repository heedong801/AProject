// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	//PrintViewport(1.f, FColor::Red, TEXT("BeginPlay"));

	m_Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::TriggerBeginOverlap);
	m_Trigger->OnComponentEndOverlap.AddDynamic(this, &ATrigger::TriggerEndOverlap);
	//PrintViewport(1.f, FColor::Red, TEXT("ATrigger::BeginPlay()"));

	//if (m_Trigger->OnComponentBeginOverlap.IsBound() == true)
	//	PrintViewport(1.f, FColor::Red, TEXT("ATrigger Begin True"));
	//else
	//	PrintViewport(1.f, FColor::Red, TEXT("ATrigger Begin False"));

	//if (m_Trigger->OnComponentEndOverlap.IsBound() == true)
	//	PrintViewport(1.f, FColor::Red, TEXT("ATrigger End True"));
	//else
	//	PrintViewport(1.f, FColor::Red, TEXT("ATrigger End False"));
	//_Trigger->OnComponentBeginOverlap.Broadcast();
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigger::TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PrintViewport(1.f, FColor::Red, TEXT("TriggerBeginOverlap"));

	if (m_TriggerBeginDelegate.IsBound() == true)
	{
		//PrintViewport(1.f, FColor::Red, TEXT("Good"));

		m_TriggerBeginDelegate.Broadcast();
	}

}
void ATrigger::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	//PrintViewport(1.f, FColor::Red, TEXT("TriggerEndOverlap"));

	m_TriggerEndDelegate.Broadcast();
}
