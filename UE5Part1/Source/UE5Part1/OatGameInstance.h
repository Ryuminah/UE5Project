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

	// ����ü�� �𸮾� ������Ʈ�� �ƴϱ� ������, NewObject�� Ȱ������ �ʴ´�.
	// ���� ���ڰ� �ִ� �����ڸ� ����
	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder){ }

	// UObject* Ÿ���� �ƴϱ� ������, UPROPERTY()���� �ǰ�, �ƴϾ �����ϴ�.
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

	// �޸𸮸� ������ �ʿ䰡 ���� ������, UPROPERTY()�� ������ ����.
	TArray<FStudentData> StudentArray;
	TMap<int32, FString> StudentsMap;

	// �𸮾� ������Ʈ�� �������� ���·� TArray���ο��� ������ ���
	// �ʼ������� UPROPERTY()�� �ٿ��� ��.
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	// �Ϲ� ��ü�� UPROPERTY()�� ����� �� ����
	// FStudent ������ UObject�� ������ �÷��Ϳ� ���� ������ �޸𸮰� ȸ����. 
	class FStudentManager* StudentManager = nullptr;

};
