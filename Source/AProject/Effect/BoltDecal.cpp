// Fill out your copyright notice in the Description page of Project Settings.


#include "BoltDecal.h"
#include "../DebugClass.h"
ABoltDecal::ABoltDecal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DcalMtrlAsset(TEXT("MaterialInstanceConstant'/Game/Player/Wukong/Material/MT_MagicCircle_Inst.MT_MagicCircle_Inst'"));

	if (DcalMtrlAsset.Succeeded())
		m_Decal->SetDecalMaterial(DcalMtrlAsset.Object);
}

void ABoltDecal::Tick(float DeltaTime)
{
	if (m_SkillOn)
	{

		FHitResult result;
		bool Hit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);

		if (Hit)
		{
			SetActorLocation(result.ImpactPoint);
		}
	}
}