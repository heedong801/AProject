// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageUI.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UDamageUI : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTextBlock* m_DamageText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector m_Location;

	UPROPERTY(meta = (BindWidgetAnim), meta = (AllowPrivateAccess = "true"), Transient)
		class UWidgetAnimation* m_FadeAnim;

	bool m_Active;
public:
	void SetDamage(const int32& Damage) { m_Damage = Damage; }
	void SetLocation(const FVector& Loc) { m_Location = Loc; }

	void SetActive(bool bOnActive);
	bool GetActive();

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player);

};