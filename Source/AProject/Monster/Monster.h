// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MonsterInfo.h"
#include "../Etc/PatrolPointSpline.h"
#include "GameFramework/Character.h"
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

	float m_CurrentPatrolLength;
	int32 m_CurrentPatrolIndex;

	bool m_PatrolEnable;
	class APatrolPointSpline* m_PatrolSpline;
	float m_PatrolLength;

	FString m_MonsterInfoName;

	class UMonsterAnimInstance* m_AnimInstance;

	FTimerHandle m_MonsterDeathTimer;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void NormalAttack() {}
	virtual void Death() {}
	FVector GetPatrolPoint();
	void SetPatrolPointSpline(class APatrolPointSpline* Spline){		m_PatrolSpline = Spline;	}
	void NextPatrolPoint();
	FVector GetPatrolPointSpline() {		return m_PatrolSpline->GetSplinePoint(m_CurrentPatrolLength);	}
	bool GetPatrolWait() {		return m_PatrolLength / 3.f * (m_CurrentPatrolIndex + 1) <= m_CurrentPatrolLength;	}

	void ChangeAnimType(EMonsterAnimType Type);
	FMonsterInfo& GetMonsterInfo(){		return m_MonsterInfo;	}

	void SetPatrolEnable(bool Enable)	{		m_PatrolEnable = Enable;	}
	bool GetAttackEnd()	{		return m_AttackEnd;		}
	void SetAttackEnd(bool AttackEnd)	{m_AttackEnd = AttackEnd;	}

};
