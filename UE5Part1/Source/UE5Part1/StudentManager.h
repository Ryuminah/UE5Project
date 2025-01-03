// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// 일반 C++ 객체의 경우 F접두어를 사용한다.
// UPROPERTY()나 UObject를 관리할 수 있는 능력이 전혀 없음.
class UE5PART1_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {};
	~FStudentManager();

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	// 고유한 클래스 네임을 지정
	virtual FString GetReferencerName() const override { return TEXT("FStudentManager"); }

public:
	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	// 가비지 컬렉터에 의해 무조건 메모리가 회수됨. 
	class UStudent* SafeStudent = nullptr;
};
