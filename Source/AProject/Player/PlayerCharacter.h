// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "PlayerInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class APROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* m_Arm;

	class UPlayerAnim* m_AnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_SkyAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FPlayerInfo	m_PlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_SkillMontageArray;

	int32 MaxExp;

	bool m_ActiveWidget;
	bool m_Movable;

	FString m_PlayerInfoName;

	FTimerHandle TimeDillationHandle;
	FTimerHandle RecoveryHandle;
	FTimerHandle ComboTimerHandle;

	bool m_ActiveComboTime;
	int32 m_ComboCnt;
	int32 m_SkillIdx;
	
	float m_LaunchPower;
	FRotator m_ArmRotInitYaw;

	bool m_IsSprint;
	bool m_IsCritical;

	bool m_IsInTown;
	bool m_IsInDungeonTrigger;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

public:
	void MoveForward(float Scale);
	void MoveRight(float Scale);
	void LookUp(float Scale);
	void Turn(float Scale);
	void SetDirection();
	void ZoomInKey(float Scale);
	void JumpKey();
	void AttackKey();
	void Sprint();
	void StopSprint();
	void QuestKey();
	void QuitKey();
	void InteractionKey();

	void Skill1Key();
	void Skill2Key();
	void Skill3Key();

	void ResetCombo() { m_ActiveComboTime = false; m_ComboCnt = 0; }
	void Recovery();
	void SetActiveWidget(bool ActiveWidget) { m_ActiveWidget = ActiveWidget; }
	void SetTimeDillation();
	FPlayerInfo& GetPlayerInfo()	{ return m_PlayerInfo;}

	void AddExp(int32 Exp);
	void AddGold(int32 Gold);
	void CameraArmYawReset();
	void SetCameraArmYaw(FRotator Init) {		m_ArmRotInitYaw = Init;	}
	virtual int32 GetCurrentCombo() { return 0; } 
	virtual void SetCurrentCombo(int32 curCombo) { } 
	virtual void HitDamage() { }
	virtual void UseSkill(int32 Idx);
	virtual void Attack();
	UAnimMontage* GetSkyAttackMontage() { return m_SkyAttackMontage; }
	virtual bool SkillPlayAnim(int32 idx);
	int32 GetSkillIdx() { return m_SkillIdx; }
	float GetLauchPower() { return m_LaunchPower; }
	void SetLaunchPower(float Power) { m_LaunchPower = Power; }
	float GetMovable() { return m_Movable; }
	void SetMovable(bool Movable) { m_Movable = Movable; }
	bool GetCritical() { return m_IsCritical; }
	void SetCritical(bool Critical) { m_IsCritical = Critical; }
	bool GetInTown() { return m_IsInTown; }
	void SetInTown(bool InTown) { m_IsInTown = InTown; }
	bool GetInDungeonTrigger() { return m_IsInDungeonTrigger; }
	void SetInDungeonTrigger(bool InDungeonTrigger) { m_IsInDungeonTrigger = InDungeonTrigger; }
	UFUNCTION()
	void SetTimeDefaultTimeDilation();
	//struct FPlayerTraceInfo APlayerCharacter::FootTrace(float fTraceDistance, FName sSocket);

	//UFUNCTION()
	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};

