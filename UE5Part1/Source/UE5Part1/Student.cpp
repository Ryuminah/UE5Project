// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("Default");
	Order = -1;
	//Card->SetCardType(ECardType::Student);
}

void UStudent::Serialize(FArchive& Ar)
{
	// 언리얼 오브젝트가 가져야하는 기본적인 정보들을 Super에서 처리해줌
	Super::Serialize(Ar);

	// 프로퍼티의 데이터 쓰는 순서만 지정하면 됨.
	Ar << Order;
	Ar << Name;
}
