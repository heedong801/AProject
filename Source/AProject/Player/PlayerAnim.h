// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Ground,
	Sky
};

UCLASS()
class APROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()


public:
	UPlayerAnim();

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_Dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_Attack;

	bool m_CanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_UseFullbody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EPlayerAnimType m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_OnSky;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_DoubleJump;
	// UFUNCTION	///////////////////////////////////////////////////////////////////
	UFUNCTION()
		void AnimNotify_AttackCombo();
	UFUNCTION()
		void AnimNotify_HitDamage();

public:
	void SetDirection(float Dir){m_Dir = Dir;}
	bool GetCanAttack() { return m_CanAttack; }
	void SetCanAttack(bool AttackEnable) { m_CanAttack = AttackEnable; }
	FName GetAttackMontageSectionName(int32 Section);

	void SetIsAttack(bool Attack) { m_Attack = Attack; }
	bool IsAttack()	const{return m_Attack;}

	void SetDoubleJump(bool jump) { m_DoubleJump = jump; }
	bool GetDoubleJump()	const { return m_DoubleJump; }

	
	void SetFullbody(float useFullbody);
	float GetFullbody() { return m_UseFullbody; }

	void ChangeAnimType(EPlayerAnimType Type){	m_AnimType = Type;	}

	EPlayerAnimType GetAnimType()	{	return m_AnimType;	}
};

//UFUNCTION()
//	void AnimNotify_FallEnd();
//UFUNCTION()
//	void AnimNotify_NormalAttack();
//UFUNCTION()
//	void AnimNotify_AttackCombo();
//UFUNCTION()
//	void AnimNotify_SkillFire();
//UFUNCTION()
//	void AnimNotify_SkillVoice();
//UFUNCTION()
//	void AnimNotify_LeftStep();
//UFUNCTION()
//	void AnimNotify_RightStep();
//UFUNCTION()
//	void AnimNotify_FallRecoveryEnd();
//UFUNCTION()
//	void AnimNotify_Skill3Fire();
//UFUNCTION()
//	void AnimNotify_GhostTrailEnd();
