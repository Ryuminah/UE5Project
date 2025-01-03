// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"

FStudentManager::~FStudentManager()
{
}

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	// 해당 UObject가 엔진의 관리하에 있는지 체크
	// 가상 함수 테이블과 메모리 할당 상태를 기반으로 확인한다.
	// 1. 객체가 실제로 메모리에 존재하는지 / UObject 클래스의 메타데이터를 올바르게 참조하고 있는지 / 3. 객체가 엔진의 UObject 관리 시스템 내에 있는지
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}
