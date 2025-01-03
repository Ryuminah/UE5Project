// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// �Ϲ� C++ ��ü�� ��� F���ξ ����Ѵ�.
class UE5PART1_API FStudentManager
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {};
	~FStudentManager();

	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	class UStudent* SafeStudent = nullptr;
};
