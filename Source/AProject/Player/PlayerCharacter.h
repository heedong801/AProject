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

	bool m_ActiveWidget;
	FString m_PlayerInfoName;
	FTimerHandle TimeDillationHandle;
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
	void SetActiveWidget(bool ActiveWidget) { m_ActiveWidget = ActiveWidget; }
	void SetTimeDillation();
	const FPlayerInfo& GetPlayerInfo()	const { return m_PlayerInfo;}

	void AddExp(int32 Exp);
	void AddGold(int32 Gold);

	virtual int32 GetCurrentCombo() { return 0; } 
	virtual void SetCurrentCombo(int32 curCombo) { } 
	virtual void HitDamage() { }

	UAnimMontage* GetSkyAttackMontage() { return m_SkyAttackMontage; }

	UFUNCTION()
	void SetTimeDefaultTimeDilation();
	//struct FPlayerTraceInfo APlayerCharacter::FootTrace(float fTraceDistance, FName sSocket);

	//UFUNCTION()
	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};

