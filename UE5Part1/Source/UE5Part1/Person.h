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
	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }


protected:
	UPROPERTY()
	FString Name;

	// UE5 style
	UPROPERTY()
	TObjectPtr<class UCard> Card;

private:

};
