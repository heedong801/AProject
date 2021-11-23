 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssetPathMain.generated.h"

USTRUCT()
struct FAssetPathInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Path")
		FString Name;

	UPROPERTY(EditAnywhere, Category = "Path")
		FSoftObjectPath Path;
};

UCLASS(config=MainAsset)
class APROJECT_API UAssetPathMain : public UObject
{
	GENERATED_BODY()
	
public:
	UAssetPathMain();
	
private:
	UPROPERTY(Config)
		TArray<FAssetPathInfo> MaterialPathArray;

	UPROPERTY(Config)
		TArray<FAssetPathInfo> SoundPathArray;

	UPROPERTY(Config)
		TArray<FAssetPathInfo> ParticlePathArray;

	TMap<FString, FSoftObjectPath> m_mapMaterialPath;
	TMap<FString, FSoftObjectPath> m_mapSoundPath;
	TMap<FString, FSoftObjectPath> m_mapParticlePath;
public:
	void ConvertPath();
	const FSoftObjectPath* FindPath(const FString& Name);
	const FSoftObjectPath* FindSoundPath(const FString& Name);
	const FSoftObjectPath* FindParticlePath(const FString& Name);
};
