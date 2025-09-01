// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HWPlayerController.h"
#include "UI/HWChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/HWGameModeBase.h"
#include "HW_09/HW_09.h"
#include "Player/HWPlayerState.h"
#include "Net/UnrealNetwork.h"


AHWPlayerController::AHWPlayerController()
{
	bReplicates = true;
}

void AHWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UHWChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UHWChatInput>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void AHWPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		AHWPlayerState* HWPS = GetPlayerState<AHWPlayerState>();
		if (IsValid(HWPS) == true)
		{
			FString CombinedMessageString = HWPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void AHWPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	HW_09FunctionLibrary::MyPrintString(this,InChatMessageString, 10.f);
}

void AHWPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, NotificationText);
}

void AHWPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AHWPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AHWGameModeBase* HWGM = Cast<AHWGameModeBase>(GM);
		if (IsValid(HWGM) == true)
		{
			HWGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}
