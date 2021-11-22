// Copyright Epic Games, Inc. All Rights Reserved.


#include "AProjectGameModeBase.h"

AAProjectGameModeBase::AAProjectGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Wukong/BP_Wukong.BP_Wukong_C'"));
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;
}