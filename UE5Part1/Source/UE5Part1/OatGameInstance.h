// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OatGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5PART1_API UOatGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UOatGameInstance();

	virtual void Init() override;

private:
	// ���÷��� �ý��� ��ũ��
	UPROPERTY()
	FString SchoolName;
	
};
