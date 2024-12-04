// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	Name = TEXT("선생");
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	// 클래스 정보에 대해서는 단일 상속만 지원함.
	// Super클래스가 UPerson으로 지정되어 있기 때문에, Super::DoLesson()은 사용할 수 없다. 
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s 강의중"), *Name);
}

