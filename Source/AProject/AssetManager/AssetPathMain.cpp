// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetPathMain.h"
#include "../DebugClass.h"

UAssetPathMain::UAssetPathMain()
{

}

void UAssetPathMain::ConvertPath()
{
	LOG(TEXT("LOAD"));

	for (auto& result : MaterialPathArray)
	{
		m_mapMaterialPath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());

	}

	for (auto& result : SoundPathArray)
	{
		m_mapSoundPath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());

	}

	for (auto& result : ParticlePathArray)
	{
		m_mapParticlePath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());

	}
}

const FSoftObjectPath* UAssetPathMain::FindPath(const FString& Name)
{
	return m_mapMaterialPath.Find(Name);
}

const FSoftObjectPath* UAssetPathMain::FindSoundPath(const FString& Name)
{
	return m_mapSoundPath.Find(Name);
}
const FSoftObjectPath* UAssetPathMain::FindParticlePath(const FString& Name)
{
	return m_mapParticlePath.Find(Name);
}