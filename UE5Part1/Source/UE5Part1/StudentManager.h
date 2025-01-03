// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// 일반 C++ 객체의 경우 F접두어를 사용한다.
class UE5PART1_API FStudentManager
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {};
	~FStudentManager();

	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	class UStudent* SafeStudent = nullptr;
};
