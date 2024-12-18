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
	// TObjectPtr을 이용해서 전방선언
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;
	
	// 리플렉션 시스템 매크로
	UPROPERTY()
	FString SchoolName;

	
};
