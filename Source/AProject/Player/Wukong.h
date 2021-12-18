// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Wukong.generated.h"

UCLASS()
class APROJECT_API AWukong : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWukong();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual int32 GetCurrentCombo() { return m_CurrentCombo; }
	virtual void SetCurrentCombo(int32 curCombo);
	virtual void HitDamage();
	virtual void UseSkill(int32 Idx);
	virtual void Attack();

	void SlamDamage();
	void SetCanAttack();
	UFUNCTION()
	void LighteningBolt();
	void FuryLighteningBolt();

	void SetFuryMode();
	void UnSetFuryMode();

	bool GetFuryMode() { return m_FuryMode; }
	bool SkillPlayAnim(int32 idx);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_AttackMontageArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_SkyAttackMontageArray;

	int32 m_MaxCombo;
	int32 m_CurrentCombo;
	int32 m_BoltCnt;
	int32 m_FuryBombCnt;

	bool m_OnSkillBolt;
	FTimerHandle m_BoltTimerHandler;
	FTimerHandle m_FuryModeTimerHandler;

	bool m_FuryMode;
	UParticleSystemComponent* m_FuryAuraEffect;
	class UPlayerAnim* m_FuryAnimInst;
	class ABoltDecal* m_BoltDecal;
	FVector m_BoltImpactPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* m_FuryWukongMesh;
	//TArray<TSubclassOf<APawn>> m_WukongBP;
};
