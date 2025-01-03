// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// �Ϲ� C++ ��ü�� ��� F���ξ ����Ѵ�.
// UPROPERTY()�� UObject�� ������ �� �ִ� �ɷ��� ���� ����.
class UE5PART1_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {};
	~FStudentManager();

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	// ������ Ŭ���� ������ ����
	virtual FString GetReferencerName() const override { return TEXT("FStudentManager"); }

public:
	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	// ������ �÷��Ϳ� ���� ������ �޸𸮰� ȸ����. 
	class UStudent* SafeStudent = nullptr;
};
