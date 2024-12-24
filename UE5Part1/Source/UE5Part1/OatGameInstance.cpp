// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "Algo/Accumulate.h"

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
	
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 i = 1; i <= ArrayNum; ++i)
	{
		Int32Array.Add(i);
	}

	// 조건에 해당하는 구문을 람다로 넣기
	Int32Array.RemoveAll([](int32 Val) {return Val % 2 == 0; });
	// 예상값 -> {1,3,5,7,9}

	Int32Array += {2, 4, 6, 8, 10};
	TArray<int32> Int32CompareArray;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };

	// 초기화 되지 않은 데이터를 빠르게 넣어줌
	Int32CompareArray.AddUninitialized(ArrayNum);

	//C 스타일의 메모리 복사
	FMemory::Memcpy(Int32CompareArray.GetData(), CArray, sizeof(int32) * ArrayNum);
	ensure(Int32Array == Int32CompareArray);


	FString strArray = TEXT("");
	for (auto i : Int32Array )
	{
		strArray += FString::FromInt(i);
	}
	UE_LOG(LogTemp, Log, TEXT("기존 : %s"),*strArray);

	FString strCopy = TEXT("");

	for (auto i : Int32CompareArray)
	{
		strCopy += FString::FromInt(i);
	}
	UE_LOG(LogTemp, Log, TEXT("복사 : %s"), *strCopy);

	int32 Sum = Algo::Accumulate(Int32Array,0);
	UE_LOG(LogTemp, Log, TEXT("총 합: %d"), Sum);

	UE_LOG(LogTemp, Log, TEXT("============================================"));
}
 