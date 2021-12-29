// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnim.h"
#include "../DebugClass.h"
#include "../AProjectGameInstance.h"
#include "../UI/CharacterHUD.h"
#include "../UI/MainHUD.h"
#include "../UI/SkillImageWidget.h"
#include "../AProjectGameModeBase.h"
#include "../Trigger/DungeonUITrigger.h"

//#include "../Effect/HitCameraShake.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	

	m_Arm->SetupAttachment(GetMesh());
	m_Camera->SetupAttachment(m_Arm);

	m_Arm->TargetArmLength = 1000.f;

	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	m_ActiveWidget = false;
	m_LaunchPower = 1.f;
	m_Movable = true;
	MaxExp = 100;
	m_IsCritical = false;
	m_ActiveComboTime = false;
	m_ComboCnt = 0;
	
	//LOG(TEXT("%f %f %f"), m_Arm->GetRelativeRotation().Vector().X, m_Arm->GetRelativeRotation().Vector().Y, m_Arm->GetRelativeRotation().Vector().Z);
	GetMesh()->bReceivesDecals = false;

}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Damage == 0.f)
		return 0.f;

	Damage = Damage - m_PlayerInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;
	//LOG(TEXT("%f %f %f"), m_Arm->GetRelativeRotation().Vector().X, m_Arm->GetRelativeRotation().Vector().Y, m_Arm->GetRelativeRotation().Vector().Z);
	m_PlayerInfo.HP -= Damage;

	/*GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(
		UHitCameraShake::StaticClass());*/

	//죽은경우
	if (m_PlayerInfo.HP <= 0)
	{
		//ChangeAnimType(EPlayerAnimType::Death);

		//AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
		//if (MonsterController)
		//{
		//	/*MonsterController->RunBehaviorTree(nullptr);
		//	Destroy();*/

		//	MonsterController->BrainComponent->StopLogic(TEXT("DEAD"));
		//}
		LOG(TEXT("DIE"));
	}

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

			if (IsValid(CharacterHUD))
			{
				CharacterHUD->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);
			}
		}
	}
	return Damage;
}


void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAProjectGameInstance* GameInst = Cast<UAProjectGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const FPlayerInfo* Info = GameInst->FindPlayerInfo(m_PlayerInfoName);

		const FPlayerInfo& SavePlayerInfo = GameInst->GetPlayerInfo();

		if (SavePlayerInfo.Name.IsEmpty() == false)
		{
			m_PlayerInfo.Name = SavePlayerInfo.Name;
			m_PlayerInfo.Attack = SavePlayerInfo.Attack;
			m_PlayerInfo.Armor = SavePlayerInfo.Armor;
			m_PlayerInfo.HP = SavePlayerInfo.HP;
			m_PlayerInfo.HPMax = SavePlayerInfo.HPMax;
			m_PlayerInfo.MP = SavePlayerInfo.MP;
			m_PlayerInfo.MPMax = SavePlayerInfo.MPMax;
			m_PlayerInfo.Level = SavePlayerInfo.Level;
			m_PlayerInfo.Exp = SavePlayerInfo.Exp;
			m_PlayerInfo.Gold = SavePlayerInfo.Gold;
			m_PlayerInfo.AttackDistance = SavePlayerInfo.AttackDistance;
			m_PlayerInfo.AttackAngle = SavePlayerInfo.AttackAngle;
			m_PlayerInfo.MoveSpeed = SavePlayerInfo.MoveSpeed;
			m_PlayerInfo.SkillTree = SavePlayerInfo.SkillTree;
			m_PlayerInfo.CriticalPercent = SavePlayerInfo.CriticalPercent;
			m_PlayerInfo.CriticalDamage = SavePlayerInfo.CriticalDamage;

		}
		else if (Info)
		{
			m_PlayerInfo.Name = Info->Name;
			m_PlayerInfo.Attack = Info->Attack;
			m_PlayerInfo.Armor = Info->Armor;
			m_PlayerInfo.HP = Info->HP;
			m_PlayerInfo.HPMax = Info->HPMax;
			m_PlayerInfo.MP = Info->MP;
			m_PlayerInfo.MPMax = Info->MPMax;
			m_PlayerInfo.Level = Info->Level;
			m_PlayerInfo.Exp = Info->Exp;
			m_PlayerInfo.Gold = Info->Gold;
			m_PlayerInfo.AttackDistance = Info->AttackDistance;
			m_PlayerInfo.AttackAngle = Info->AttackAngle;
			m_PlayerInfo.MoveSpeed = Info->MoveSpeed;
			m_PlayerInfo.SkillTree = Info->SkillTree;
			m_PlayerInfo.CriticalPercent = Info->CriticalPercent;
			m_PlayerInfo.CriticalDamage = Info->CriticalDamage;

		}

	}

}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//LOG(TEXT("A : %s"), *GetMesh()->GetName());
	m_AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	m_ArmRotInitYaw = m_Arm->GetRelativeRotation();
	
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	UMainHUD* MainHUD = GameMode->GetMainHUD();

	if (IsValid(MainHUD))
	{
		UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

		if (IsValid(CharacterHUD))
		{
			TArray<USkillImageWidget*> SkillArray = CharacterHUD->GetSkillArray();

			for (int32 i = 0; i < SkillArray.Num(); ++i)
			{
				if (m_PlayerInfo.Level >= m_PlayerInfo.SkillTree[i].RequiredLevel)
				{
					SkillArray[i]->SetSkillImg(m_PlayerInfo.SkillTree[i].TexturePath);
					SkillArray[i]->SetVisibility(ESlateVisibility::Visible);
				}

			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(RecoveryHandle, this, &APlayerCharacter::Recovery,
		0.5f, true, -1.f);
	//m_AnimInst->OnMontageEnded.AddDynamic(this, &APlayerCharacter::OnAttackMontageEnded);
}

void APlayerCharacter::Recovery()
{
	//LOG(TEXT("%f"), m_PlayerInfo.HP);

	if (m_PlayerInfo.HP < m_PlayerInfo.HPMax)
		m_PlayerInfo.HP += 1.2f;
	else
		m_PlayerInfo.HP = m_PlayerInfo.HPMax;

	if (m_PlayerInfo.MP < m_PlayerInfo.MPMax)
		m_PlayerInfo.MP += 1.f;
	else
		m_PlayerInfo.MP = m_PlayerInfo.MPMax;

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	//LOG(TEXT("AA"));
	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();
		//LOG(TEXT("BB"));
		if (IsValid(MainHUD))
		{
			UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();
			//LOG(TEXT("CC"));
			if (IsValid(CharacterHUD))
			{
				CharacterHUD->SetHPPercent(m_PlayerInfo.HP / m_PlayerInfo.HPMax);
				CharacterHUD->SetMPPercent(m_PlayerInfo.MP / m_PlayerInfo.MPMax);

			}
		}
	}

}
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JumpMaxCount = 2;
	

	SetDirection();
	m_AnimInst->SetFullbody(m_AnimInst->GetCurveValue("FullBody"));
	//LOG(TEXT(" GetDoubleJump : %d"), m_AnimInst->GetDoubleJump());
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Can you see this message?"));

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &APlayerCharacter::ZoomInKey);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::AttackKey);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Skill1Key);
	PlayerInputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Skill2Key);
	PlayerInputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Skill3Key);

	PlayerInputComponent->BindAction(TEXT("Quest"), EInputEvent::IE_Pressed, this, &APlayerCharacter::QuestKey);
	PlayerInputComponent->BindAction(TEXT("Quit"), EInputEvent::IE_Pressed, this, &APlayerCharacter::QuitKey);
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &APlayerCharacter::InteractionKey);
	PlayerInputComponent->BindAction(TEXT("Equipment"), EInputEvent::IE_Pressed, this, &APlayerCharacter::EquipmentKey);
}

void APlayerCharacter::EquipmentKey()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UEquipmentWidget* EquipmentWidget = MainHUD->GetEquipment();
			{
				if (IsValid(EquipmentWidget))
				{
					if (EquipmentWidget->GetVisibility() == ESlateVisibility::Collapsed)
					{
						EquipmentWidget->SetVisibility(ESlateVisibility::Visible);

						APlayerController* ControllerA = GetWorld()->GetFirstPlayerController();

						FInputModeGameAndUI Mode;

						ControllerA->SetInputMode(Mode);
						ControllerA->SetIgnoreLookInput(true);
						ControllerA->bShowMouseCursor = true;
						m_ActiveWidget = true;
					}
					else
					{
						EquipmentWidget->SetVisibility(ESlateVisibility::Collapsed);

						APlayerController* ControllerA = GetWorld()->GetFirstPlayerController();

						FInputModeGameOnly	Mode;
						//FInputModeGameOnly
						//FInputModeGameAndUI	Mode;

						ControllerA->SetInputMode(Mode);
						ControllerA->SetIgnoreLookInput(false);
						ControllerA->bShowMouseCursor = false;
						m_ActiveWidget = false;
					}
				}
			}
		}
	}
}
void APlayerCharacter::Skill1Key()
{
	m_SkillIdx = 0;
	SkillPlayAnim(m_SkillIdx);

}

void APlayerCharacter::Skill2Key()
{
	m_SkillIdx = 1;
	SkillPlayAnim(m_SkillIdx);

}
void APlayerCharacter::Skill3Key()
{
	m_SkillIdx = 2;
	SkillPlayAnim(m_SkillIdx);

}
bool APlayerCharacter::SkillPlayAnim(int32 idx)
{
	if (m_IsInTown == false)
	{
		if (m_PlayerInfo.MP > m_PlayerInfo.SkillTree[idx].RequiredMP && m_PlayerInfo.Level >= m_PlayerInfo.SkillTree[idx].RequiredLevel)
		{
			if (m_AnimInst->GetOnSky() == false && m_AnimInst->GetCanAttack() == true)
			{
				AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

				if (IsValid(GameMode))
				{
					UMainHUD* MainHUD = GameMode->GetMainHUD();

					if (IsValid(MainHUD))
					{
						UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

						if (IsValid(CharacterHUD))
						{
							TArray<USkillImageWidget*> SkillArray = CharacterHUD->GetSkillArray();

							if (SkillArray[idx]->GetCoolTimeOn() == true)
							{
								if (!m_AnimInst->Montage_IsPlaying(m_SkillMontageArray[idx]))
								{
									m_AnimInst->Montage_SetPosition(m_SkillMontageArray[idx], 0.f);
									m_AnimInst->Montage_Play((m_SkillMontageArray[idx]));
									SkillArray[idx]->SetCoolTimePercent(1.f, m_PlayerInfo.SkillTree[idx].CoolTime);
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
void APlayerCharacter::QuestKey()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	
	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UQuestWidget* QuestWidget = MainHUD->GetQuestWidget();
			{
				if (IsValid(QuestWidget))
				{
					if (QuestWidget->GetVisibility() == ESlateVisibility::Collapsed)
					{
						QuestWidget->SetVisibility(ESlateVisibility::Visible);

						APlayerController* ControllerA = GetWorld()->GetFirstPlayerController();

						FInputModeGameAndUI Mode;

						ControllerA->SetInputMode(Mode);
						ControllerA->SetIgnoreLookInput(true);
						ControllerA->bShowMouseCursor = true;
						m_ActiveWidget = true;
					}
					else
					{
						QuestWidget->SetVisibility(ESlateVisibility::Collapsed);

						APlayerController* ControllerA = GetWorld()->GetFirstPlayerController();

						FInputModeGameOnly	Mode;
						//FInputModeGameOnly
						//FInputModeGameAndUI	Mode;

						ControllerA->SetInputMode(Mode);
						ControllerA->SetIgnoreLookInput(false);
						ControllerA->bShowMouseCursor = false;
						m_ActiveWidget = false;
					}
				}
			}
		}
	}
}

void APlayerCharacter::SetDirection()
{
	//LOG(TEXT("%f %f %f"), m_Arm->GetRelativeRotation().Vector().X, m_Arm->GetRelativeRotation().Vector().Y, m_Arm->GetRelativeRotation().Vector().Z);

	FRotator rot = GetActorRotation();

	FRotator lookRot = GetVelocity().Rotation();

	FRotator result = (rot - lookRot);
	result.Normalize();

	m_AnimInst->SetDirection(result.Yaw * -1);
}
void APlayerCharacter::MoveForward(float Scale)
{
	if(!m_ActiveWidget && m_Movable )
		AddMovementInput(GetActorForwardVector(), Scale);
}

void APlayerCharacter::MoveRight(float Scale)
{
	if (!m_ActiveWidget && m_Movable && !m_IsSprint)
		AddMovementInput(GetActorRightVector(), Scale);
}

void APlayerCharacter::LookUp(float Scale)
{
	if (!m_ActiveWidget)
	{
		if (m_Movable)
			AddControllerYawInput(Scale * 0.3f);
		else
		{
			FRotator Rot = m_Arm->GetRelativeRotation();

			Rot.Yaw += Scale * 50.f * GetWorld()->GetDeltaSeconds();

			m_Arm->SetRelativeRotation(Rot);
		}
	}

}

void APlayerCharacter::CameraArmYawReset()
{
	m_Arm->SetRelativeRotation(m_ArmRotInitYaw);
}

void APlayerCharacter::Turn(float Scale)
{
	if (!m_ActiveWidget)
	{
		FRotator Rot = m_Arm->GetRelativeRotation();

		Rot.Pitch += Scale * 10.f * GetWorld()->GetDeltaSeconds();

		Rot.Pitch = FMath::Clamp(Rot.Pitch, -45.f, 0.f);
		
		m_Arm->SetRelativeRotation(Rot);
	}
}

void APlayerCharacter::ZoomInKey(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 20.f;

	m_Arm->TargetArmLength = FMath::Clamp(m_Arm->TargetArmLength, 350.f, 1000.f);
}

void APlayerCharacter::Attack()
{}

void APlayerCharacter::AttackKey()
{
	if(!m_IsInTown)
		Attack();
}

void APlayerCharacter::InteractionKey()
{
	FHitResult HitResult;
	FCollisionQueryParams params(NAME_None, false, this); //몬스터제외

	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel9
		, FCollisionShape::MakeSphere(100.f), params);

	if (Sweep)
	{
		ADungeonUITrigger* DungeonTrigger = Cast<ADungeonUITrigger>(HitResult.Actor);
		if (DungeonTrigger)
		{
			DungeonTrigger->Interaction();
		}
	}

}
void APlayerCharacter::QuitKey()
{
	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			MainHUD->QuitAllWidget();

			APlayerController* ControllerA = GetWorld()->GetFirstPlayerController();

			FInputModeGameOnly	Mode;
			//FInputModeGameOnly
			//FInputModeGameAndUI	Mode;

			ControllerA->SetInputMode(Mode);
			ControllerA->SetIgnoreLookInput(false);
			ControllerA->bShowMouseCursor = false;
			m_ActiveWidget = false;
		}
	}
}
void APlayerCharacter::JumpKey()
{
	//LOG(TEXT("%d"), JumpCurrentCount);
	if (m_AnimInst->GetAnimType() == EPlayerAnimType::Ground || JumpCurrentCount == 1)
	{
		Jump();
		
		if (JumpCurrentCount == 1)
		{
			m_AnimInst->SetDoubleJump(true);
		}

	
		m_AnimInst->ChangeAnimType(EPlayerAnimType::Sky);
	}
}

//void APlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	LOG(TEXT("END"));
//	m_AnimInst->SetCanAttack(true);
//	m_AnimInst->SetIsAttack(false);
//	SetCurrentCombo(0);
//}

void APlayerCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= 1.5;
	m_IsSprint = true;
}
void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= 1.5;
	m_IsSprint = false;
}

void APlayerCharacter::SetTimeDefaultTimeDilation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);

}

void APlayerCharacter::SetTimeDillation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(0.5f);
	GetWorld()->GetTimerManager().SetTimer(TimeDillationHandle,
		this, &APlayerCharacter::SetTimeDefaultTimeDilation, 1.f, false, 0.25f);
}

void APlayerCharacter::AddExp(int32 Exp)
{
	m_PlayerInfo.Exp += Exp;

	AAProjectGameModeBase* GameMode = Cast<AAProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (IsValid(GameMode))
	{
		UMainHUD* MainHUD = GameMode->GetMainHUD();

		if (IsValid(MainHUD))
		{
			UCharacterHUD* CharacterHUD = MainHUD->GetCharacterHUD();

			if (IsValid(CharacterHUD))
			{
				if (m_PlayerInfo.Exp >= MaxExp)
				{
					m_PlayerInfo.Exp = 0;
					m_PlayerInfo.Level++;

					int LevelUpDamage = 2;
					int LevelUpArmor = 5;
					int LevelUpHp = 25;
					int LevelUpMp = 15;

					m_PlayerInfo.Attack += LevelUpDamage;
					m_PlayerInfo.Armor += LevelUpArmor;
					m_PlayerInfo.HPMax += LevelUpHp;
					m_PlayerInfo.MPMax += LevelUpMp;

					MaxExp *= 2;
					CharacterHUD->SetLevelText(m_PlayerInfo.Level);

					TArray<USkillImageWidget*> SkillArray = CharacterHUD->GetSkillArray();

					for (int32 i = 0; i < SkillArray.Num(); ++i)
					{
						if (m_PlayerInfo.Level >= m_PlayerInfo.SkillTree[i].RequiredLevel)
						{
							SkillArray[i]->SetSkillImg(m_PlayerInfo.SkillTree[i].TexturePath);

							SkillArray[i]->SetVisibility(ESlateVisibility::Visible);
						}
					}
				}
				
				CharacterHUD->SetEXPPercent(m_PlayerInfo.Exp / (float)MaxExp);
			}
		}
	}

}

void APlayerCharacter::UseSkill(int32 Idx)
{

}

void APlayerCharacter::AddGold(int32 Gold)
{
	m_PlayerInfo.Gold += Gold;

}
//struct FPlayerTraceInfo APlayerCharacter::FootTrace(float fTraceDistance, FName sSocket)
//{
//	struct FPlayerTraceInfo pFPlayerTraceInfo;
//
//	//! Set Linetraces startpoint and end point
//	FVector pSocketLocation = GetMesh()->GetSocketLocation(sSocket);
//	FVector pLine_Start = FVector(pSocketLocation.X, pSocketLocation.Y, GetActorLocation().Z);
//	FVector pLine_End = FVector(pSocketLocation.X, pSocketLocation.Y
//		, (GetActorLocation().Z - m_fIKCapsuleHalkHeight) - fTraceDistance);
//
//	//! Process Line Trace
//	FHitResult pHitResult;
//	TArray<AActor*> pIgnore;
//	pIgnore.Add(GetOwner());
//
//	bool bDebug = true;
//	EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
//	if (bDebug == true) eDebug = EDrawDebugTrace::ForOneFrame;
//
//	bool bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), pLine_Start, pLine_End,
//		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, pIgnore, eDebug, pHitResult, true);
//
//	//! Set ImpactNormal and Offset from HitResult
//	pFPlayerTraceInfo.pImpactLocation = pHitResult.ImpactNormal;
//	if (pHitResult.IsValidBlockingHit() == true)
//	{
//		float fImpactLegth = (pHitResult.ImpactPoint - pHitResult.TraceEnd).Size();
//		pFPlayerTraceInfo.fOffset = 5.0f + (fImpactLegth - fTraceDistance);
//	}
//	else
//	{
//		pFPlayerTraceInfo.fOffset = 0.0f;
//	}
//
//	return pFPlayerTraceInfo;
//}