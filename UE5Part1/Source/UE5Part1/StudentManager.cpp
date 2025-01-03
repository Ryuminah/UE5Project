// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"

FStudentManager::~FStudentManager()
{
}

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	// �ش� UObject�� ������ �����Ͽ� �ִ��� üũ
	// ���� �Լ� ���̺�� �޸� �Ҵ� ���¸� ������� Ȯ���Ѵ�.
	// 1. ��ü�� ������ �޸𸮿� �����ϴ��� / UObject Ŭ������ ��Ÿ�����͸� �ùٸ��� �����ϰ� �ִ��� / 3. ��ü�� ������ UObject ���� �ý��� ���� �ִ���
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}
