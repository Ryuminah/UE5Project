// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Year = 1;
	Id = 1;
	Name = TEXT("오트1");
}

void UStudent::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d 학년 %d번 %s가 수업을 듣음"), Year, Id, *Name);
}
