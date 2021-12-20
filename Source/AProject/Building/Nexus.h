// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../Effect/NormalEffect.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "Nexus.generated.h"

UCLASS()
class APROJECT_API ANexus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANexus();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* m_HPBar;

	class UHPBar* m_HPBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_Top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_Mid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* m_Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_FirstDamagedParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_SecondDamagedParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_ThirdDamagedParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector m_NextPosition;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString m_NextStreamingLevelName;
	ANormalEffect* m_Effect;

	UMaterialInstanceDynamic* m_DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Hp;

	FTimerHandle m_ExployedTimer;
	FTimerDelegate m_TimerDelegate;
	FTimerHandle m_ClearTimer;
	FTimerHandle m_RecallTimer;
	FTimerHandle m_RecallEffectTimer;
	FTimerHandle m_PlayerRecallTimer;


	int m_ExployCnt;
	bool IsExployed;

	//////////////////////Sequence //////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ULevelSequence* m_SequenceAsset;

	ULevelSequencePlayer* m_SequencePlayer;
	ALevelSequenceActor* m_SequenceActor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float TakeDamageForNexus(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FVector HitPos, FRotator NormalRot);

	UFUNCTION()
		void Exploy(FVector HitPos, FRotator NormalRot);
	UFUNCTION()
		void CheckClear();
	UFUNCTION()
		void Recall();
	UFUNCTION()
		void PlayerRecall();
	UFUNCTION()
		void RecallEffectAfterSequence();

	UCapsuleComponent* GetCapsuleComponent() {
		return m_Body;
	}
};
