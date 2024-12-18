// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);

/**
 * 
 */
UCLASS()
class UE5PART1_API UCourseInfo : public UObject
{
	GENERATED_BODY()

public:
	UCourseInfo();

public:
	FCourseInfoOnChangedSignature OnChanged;
	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	// 메모리를 동적할당하거나, 리플렉션을 사용할 일이 없다면 UPROPERTY()를 굳이 사용하지 않아도 됨.
	FString Contents;
};
