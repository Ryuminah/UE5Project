// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR First[] = TEXT("김이박최고류한윤");
	TCHAR Middle[] = TEXT("일이삼사오육칠팔");
	TCHAR Last[] = TEXT("일이삼사오육칠팔");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = First[FMath::RandRange(0, 7)];
	RandArray[1] = Middle[FMath::RandRange(0, 7)];
	RandArray[2] = Last[FMath::RandRange(0, 7)];

	// ex) TArray -> [김][삼][팔]
	// 첫번째 포인터 값을 반환하면, 반환값이 FString이기 때문에 자동으로 만들어져서 반환된다.
	return RandArray.GetData();
}

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
	//CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("============================================"));
	

	const int32 StudentNum = 300;
	for (int32 i = 1; i <= StudentNum; ++i)
	{
		// 복사 비용을 고려하여 Emplace사용 권장
		StudentArray.Emplace(FStudentData(MakeRandomName(), i));
	}
	 
	// TArray를 TMap으로 변경 (dest , src , TPair를 만들어주는 람다 함수)
	Algo::Transform(StudentArray, StudentsMap,
		[](const FStudentData& Val) {return TPair<int32, FString>(Val.Order, Val.Name); });
	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;
	Algo::Transform(StudentArray, StudentsMapByUniqueName,
		[](const FStudentData& Val) {return TPair<FString, int32>(Val.Name, Val.Order); });
	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsMapByUniqueName.Num());

	// MultiMap의 경우 중복을 허용한다.

	UE_LOG(LogTemp, Log, TEXT("============================================"));
}
 