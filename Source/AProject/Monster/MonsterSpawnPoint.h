// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnPoint.generated.h"

UCLASS()
class APROJECT_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterSpawnPoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AMonster> m_MonsterClass;

	AMonster* m_Monster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_SpawnTime;
	float m_AccTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsActivate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Death(){		m_Monster = nullptr;	}
	void SetActive(bool flag) { IsActivate = flag; }
};