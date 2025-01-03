// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OatGameInstance.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("Default");
		Order = -1;
	}

	// 구조체는 언리얼 오브젝트가 아니기 때문에, NewObject를 활용하지 않는다.
	// 따라서 인자가 있는 생성자를 구현
	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder){ }

	// UObject* 타입이 아니기 때문에, UPROPERTY()여도 되고, 아니어도 무관하다.
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

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
	virtual void Shutdown() override;


	UPROPERTY()
	FString SchoolName;

private:
	UPROPERTY()
	TArray<TObjectPtr<class UPerson>> PersonArray;

	// 메모리를 관리할 필요가 없기 때문에, UPROPERTY()를 붙이지 않음.
	TArray<FStudentData> StudentArray;
	TMap<int32, FString> StudentsMap;

	// 언리얼 오브젝트를 포인터의 형태로 TArray내부에서 관리할 경우
	// 필수적으로 UPROPERTY()를 붙여야 함.
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	// 일반 객체는 UPROPERTY()를 사용할 수 없음
	// FStudent 내부의 UObject는 가비지 컬렉터에 의해 무조건 메모리가 회수됨. 
	class FStudentManager* StudentManager = nullptr;

};
