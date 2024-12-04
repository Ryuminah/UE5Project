// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"

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

	UE_LOG(LogTemp, Log, TEXT("============================================"));
	TArray<UPerson*> Persons = { NewObject<UStudent>(),NewObject<UTeacher>() ,NewObject<UStaff>() };
	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 입장"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("============================================"));


	for (const auto Person : Persons)
	{ 
		// Person : 컨테이너의 요소를 가리키는 포인터 타입
		// Card : 이미 포인터여서 역참조가 필요 없음.
		const UCard* Card = Person->GetCard();
		check(Card);

		// 방법 1
		const UEnum* CardEnumType= FindObject<UEnum>(nullptr, TEXT("/script/UE5Part1.ECardType"));

		// 방법 2
		CardEnumType = StaticEnum<ECardType>();

		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)Card->GetCardType()).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s의 카드 타입 : %s"), *Person->GetName(), *CardMetaData);
		}
	}
}
 


