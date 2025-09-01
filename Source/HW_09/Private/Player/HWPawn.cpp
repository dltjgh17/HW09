// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HWPawn.h"
#include "HW_09/HW_09.h"

void AHWPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = HW_09FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *HW_09FunctionLibrary::GetNetModeString(this), *NetRoleString);
	HW_09FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
	
}

void AHWPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = HW_09FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *HW_09FunctionLibrary::GetNetModeString(this), *NetRoleString);
	HW_09FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}


