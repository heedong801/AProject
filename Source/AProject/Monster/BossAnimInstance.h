// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterInfo.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBossAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EBossAnimType m_AnimType;


public:
	virtual void ChangeAnimType(EBossAnimType Type)
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
	EBossAnimType GetAnimType()	const
	{
		return m_AnimType;
	}
};