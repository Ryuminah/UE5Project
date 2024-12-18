// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s 수업 듣는 중"), *Name);
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s 님이 %s로부터 밭은 메세지 : %s"), *Name ,*School, *NewCourseInfo);
}

