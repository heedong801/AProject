// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnim.h"
#include "../DebugClass.h"
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

	m_Arm->TargetArmLength = 900.f;

	static ConstructorHelpers::FClassFinder<UAnimInstance> WukongAsset(TEXT("AnimBlueprint'/Game/Player/Wukong/Anim/AB_Wukong.AB_Wukong_C'"));

	if (WukongAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(WukongAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Attack1Asset(TEXT("AnimMontage'/Game/Player/Wukong/Anim/AM_AttackA.AM_AttackA'"));

	if (Attack1Asset.Succeeded())
		m_AttackMontageArray = Attack1Asset.Object;

	GetCharacterMovement()->JumpZVelocity = 600.f;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	

}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	m_AnimInst->OnMontageEnded.AddDynamic(this, &APlayerCharacter::OnAttackMontageEnded);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	JumpMaxCount = 2;
	
	SetDirection();
	m_AnimInst->SetFullbody(m_AnimInst->GetCurveValue("FullBody"));
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



	
}
void APlayerCharacter::SetDirection()
{
	FRotator rot = GetActorRotation();

	FRotator lookRot = GetVelocity().Rotation();

	FRotator result = (rot - lookRot);
	result.Normalize();

	m_AnimInst->SetDirection(result.Yaw * -1);
}
void APlayerCharacter::MoveForward(float Scale)
{
	AddMovementInput(GetActorForwardVector(), Scale);
}

void APlayerCharacter::MoveRight(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);
}

void APlayerCharacter::LookUp(float Scale)
{
	AddControllerYawInput(Scale);

}

void APlayerCharacter::Turn(float Scale)
{
	FRotator Rot = m_Arm->GetRelativeRotation();

	Rot.Pitch += Scale * 10.f * GetWorld()->GetDeltaSeconds();

	Rot.Pitch = FMath::Clamp(Rot.Pitch, -30.f, 0.f);
	m_Arm->SetRelativeRotation(Rot);

}

void APlayerCharacter::ZoomInKey(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 20.f;

	m_Arm->TargetArmLength = FMath::Clamp(m_Arm->TargetArmLength, 350.f, 750.f);
}
void APlayerCharacter::AttackKey()
{
	

	if (m_AnimInst->GetCanAttack())
	{	
		if (GetCurrentCombo() == 0)
			m_AnimInst->Montage_Play(m_AttackMontageArray);
		else
			m_AnimInst->Montage_JumpToSection(m_AnimInst->GetAttackMontageSectionName(GetCurrentCombo() + 1));

		
		SetCurrentCombo(GetCurrentCombo() + 1);
		m_AnimInst->SetIsAttack(true);
		m_AnimInst->SetCanAttack(false);
	}
}

void APlayerCharacter::JumpKey()
{
	//LOG(TEXT("%d"), JumpCurrentCount);
	if (m_AnimInst->GetAnimType() == EPlayerAnimType::Ground || JumpCurrentCount == 1)
	{
		Jump();
		//LOG(TEXT(" GetDoubleJump : %d"), m_AnimInst->GetDoubleJump());
		
		if(JumpCurrentCount == 1)
			m_AnimInst->SetDoubleJump(true);
		//LOG(TEXT(" DDDDDDDDDDDD : %d"), m_AnimInst->GetDoubleJump());

		

		m_AnimInst->ChangeAnimType(EPlayerAnimType::Sky);
	}
}

void APlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	m_AnimInst->SetCanAttack(true);
	m_AnimInst->SetIsAttack(false);
	SetCurrentCombo(0);
}

void APlayerCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= 2;
}
void APlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= 2;
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