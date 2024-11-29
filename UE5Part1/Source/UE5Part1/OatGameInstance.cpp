// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"

UOatGameInstance::UOatGameInstance()
{
	// CDO에 해당 기본 값이 저장되어있음
	// CDO는 에디터가 활성화 되기 이전에 초기화 되기 때문에, 에디터에서 인지를 못할 수 있음.
	// 따라서 생성자 코드에서 CDO 관련 값을 변경할 떄는 에디터를 끄고 컴파일 한 뒤 실행하는 것이 안전함
	SchoolName = TEXT("기본학교");
}

void UOatGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("=============================="));
	UClass* ClassRunTime = GetClass();
	UClass* ClassCompileTime = UOatGameInstance::StaticClass();

	//check(ClassRunTime == ClassCompileTime);

	// 크래쉬 내지 않고 로그를 볼 수 있음
	//ensure(ClassRunTime != ClassCompileTime);
	//ensureMsgf(ClassRunTime != ClassCompileTime, TEXT("일부러 에러를 발생시킨 코드"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"),*ClassRunTime->GetName());
	UE_LOG(LogTemp, Log, TEXT("=============================="));

	// 생성된 인스턴스에는 이름이 설정되어 있음
	SchoolName = TEXT("청강대");
	UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("CDO : %s"), *GetClass()->GetDefaultObject<UOatGameInstance>()->SchoolName);

	UStudent* student = NewObject<UStudent>();
	UTeacher* teacher= NewObject<UTeacher>();

	FString curTeacherName;
	student->SetName(TEXT("고슬이"));
	UE_LOG(LogTemp,Log, TEXT("새로운 학생 이름 : %s"),*student->GetName());

	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		// 지정한 인스턴스의 값을 빼오는 것
		NameProp->GetValue_InContainer(teacher,&curTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님이름 : %s"), *teacher->GetName());

		curTeacherName = TEXT("오트");
		NameProp->SetValue_InContainer(teacher, &curTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님이름 : %s"), *teacher->GetName());
	}

	curTeacherName = UTeacher::StaticClass()->GetDefaultObject<UTeacher>()->GetName();
	UE_LOG(LogTemp, Log, TEXT("UTeacher CDO: %s"), *curTeacherName);
}
 