// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "LessonInterface.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UE5PART1_API UStudent : public UObject
{
	GENERATED_BODY()
	
public:
	UStudent();

	int32 GetOrder() const{ return Order; }
	void SetOrder(int32 InOrder) { Order = InOrder; }

	FString GetName() const { return Name; }
	void SetName(FString InName) { Name = InName; }

	// 직렬화를 진행할 때 필요한 함수
	virtual void Serialize(FArchive& Ar) override;

private:
	UPROPERTY()
	int32 Order;

	UPROPERTY()
	FString Name;
};
