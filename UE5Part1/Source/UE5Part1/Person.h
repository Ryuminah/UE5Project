// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UE5PART1_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	// 무조건 inline 호출을 보장해 주지는 않음
	FORCEINLINE FString& GetName() { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }


protected:
	UPROPERTY()
	FString Name;

private:

};
