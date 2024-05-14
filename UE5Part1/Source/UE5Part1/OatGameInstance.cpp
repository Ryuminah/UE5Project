﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "OatGameInstance.h"

void UOatGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT(" UOatGameInstance::Init()");
	UE_LOG(LogTemp, Log,TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR* LongCharPtr = *LogCharString;
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	if (LogCharString.Contains(TEXT("oat"), ESearchCase::IgnoreCase))
	{
		int32 Index = LogCharString.Find(TEXT("oat"), ESearchCase::IgnoreCase);
		FString EndString = LogCharString.Mid(Index);

		UE_LOG(LogTemp, Log, TEXT("Find : %s"), *EndString);

	}

	FString Left, Right;
	if (LogCharString.Split(TEXT("Oat"), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("Split : %s 와 %s"), *Left, *Right);

	}

	int32 IntValue = 32;
	float FloatValue = 3.141592;

	FString FloatIntString = FString::Printf(TEXT("Int:%d Float:%f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int:%s Float:%s"), *IntString, *FloatString);

	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	UE_LOG(LogTemp, Log, TEXT("Int:%d Float:%f"), IntValueFromString, FloatValueFromString);

	FName key1(TEXT("PELVIS"));
	FName key2(TEXT("pelvis"));

	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과 : %s"), key1 == key2 ? TEXT("true") : TEXT("false"));
}
 