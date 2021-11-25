// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EMonsterAnimType m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_Hit;

public:
	virtual void ChangeAnimType(EMonsterAnimType Type)
	{
		m_AnimType = Type;
	}
public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:
	UFUNCTION()
		void AnimNotify_HitAttack();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_HitEnd();
	EMonsterAnimType GetAnimType()	const
	{
		return m_AnimType;
	}
};