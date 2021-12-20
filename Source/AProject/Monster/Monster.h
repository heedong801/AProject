// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MonsterInfo.h"
#include "../Etc/PatrolPointSpline.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Monster.generated.h"

UCLASS()
class APROJECT_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FMonsterInfo m_MonsterInfo;

	bool m_AttackEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FVector> m_PatrolArray;
	int32 m_PatrolIdx;

	FString m_MonsterInfoName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* m_HPBar;
	class UHPBar* m_HPBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* m_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UDamageUI*> m_DamageUIArray;
	int32 m_DamageUINum;
	class UMonsterAnimInstance* m_AnimInstance;

	TSubclassOf<UUserWidget> m_DamageAsset;
	FTimerHandle m_MonsterDeathTimer;

	class APlayerCharacter* m_Player;
	bool m_IsSpawned;

	float m_TraceDistanceOrigin;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void NormalAttack() {}
	virtual void Death() {}
	FVector NextPatrolPoint();
	FVector GetPatrolPoint();

	void ChangeAnimType(EMonsterAnimType Type);
	FMonsterInfo& GetMonsterInfo(){		return m_MonsterInfo;	}

	//void SetPatrolEnable(bool Enable)	{		m_PatrolEnable = Enable;	}
	bool GetAttackEnd()	{		return m_AttackEnd;		}
	void SetAttackEnd(bool AttackEnd)	{m_AttackEnd = AttackEnd;	}
	TArray<FVector> GetPatrolArray() { return m_PatrolArray; }

	bool GetIsSpawned() { return m_IsSpawned; }
	void SetIsSpawned(bool Spawned) {		m_IsSpawned = Spawned;	}

	APlayerCharacter* GetPlayer() { return m_Player; }

	void SetDamageUI(bool Critical, float Damage);
};
