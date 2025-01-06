// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "OatGameInstance.generated.h"

// UStruct�� �ƴ� �Ϲ� C++ Struct
struct FStudentData
{
	FStudentData()
	{
		Name = TEXT("Default");
		Order = -1;
	}

	friend FArchive& operator<< (FArchive& Ar, FStudentData& InStudent)
	{
		Ar << InStudent.Name;
		Ar << InStudent.Order;
		return Ar;
	}

	FStudentData(const FString& InName, int32 InOrder) : Name(InName) , Order(InOrder){}

	FString Name = "Default";
	int32 Order = - 1;
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

	void SaveStudentPackage() const;
	void LoadStudentPackage() const;
	void LoadStudentObject() const;



private:
	UPROPERTY()
	TObjectPtr<class UStudent> StudentSrc;

	// ��Ű��/��ǥ ���� �̸� ����
	static const FString PackageName;
	static const FString AssetName;

	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> Handle;
};
