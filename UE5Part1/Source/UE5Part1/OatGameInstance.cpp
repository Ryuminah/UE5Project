// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

UOatGameInstance::UOatGameInstance()
{
	// CDO에 해당 기본 값이 저장되어있음
	// CDO는 에디터가 활성화 되기 이전에 초기화 되기 때문에, 에디터에서 인지를 못할 수 있음.
	// 따라서 생성자 코드에서 CDO 관련 값을 변경할 떄는 에디터를 끄고 컴파일 한 뒤 실행하는 것이 안전함

	// 객체가 생성될 때 당연히 필요한 것들에 대한 생성을 맡는다.
	SchoolName = TEXT("학교");
}

void UOatGameInstance::Init()
{
	Super::Init();

	// Outer를 통해 컴포지션 관계 설정 (CourseInfo를 MyGameInstance의 서브 오브젝트로 둔다.)
	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("============================================"));
	
	UStudent* student1 = NewObject<UStudent>();
	student1->SetName(TEXT("학생1"));

	UStudent* student2 = NewObject<UStudent>();
	student2->SetName(TEXT("학생2"));

	UStudent* student3 = NewObject<UStudent>();
	student3->SetName(TEXT("학생3"));

	// UObject와 클래스 멤버함수의 주소를 레퍼런스로 지정
	CourseInfo->OnChanged.AddUObject(student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("============================================"));


}
 


