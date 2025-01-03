// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "StudentManager.h"
#include "Algo/Accumulate.h"

#include "JsonObjectConverter.h"


UOatGameInstance::UOatGameInstance()
{

}

void UOatGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(TEXT("오트"), 1);

	/* 1. 경로 생성 ------------------------------------------------------------*/
	// 언리얼 프로젝트 내의 Saved 폴더의 경로를 얻어올 수 있음.
	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(),TEXT("Saved"));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *SavedDir);
	
	// 저장할 파일 이름 지정
	const FString RawDataFileName(TEXT("RawData.bin"));

	// 파일에 대한 절대경로 값
	FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *RawDataAbsolutePath);
	// 경로 정리
	FPaths::MakeStandardFilename(RawDataAbsolutePath);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *RawDataAbsolutePath);

	/* 2. 파일 데이터 쓰기 ------------------------------------------------------------*/
	// 파일에 사용할 수 있는 아카이브 클래스 생성
	FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
	
	if (nullptr != RawFileWriterAr)
	{
		// 방법1. 각각의 멤버 변수들을 직접 넣기
		/**RawFileWriterAr << RawDataSrc.Name;
		*RawFileWriterAr << RawDataSrc.Order;*/

		// 방법2. operator << 오버로딩을 통하여 구현
		*RawFileWriterAr << RawDataSrc;

		// 쓰기 완료 후 파일을 닫고 메모리 정리
		RawFileWriterAr->Close();
		delete RawFileWriterAr;
		RawFileWriterAr = nullptr;
	}

	/* 3. 파일 데이터 읽기 ------------------------------------------------------------*/
	FStudentData RawDataDest;
	FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
	if (nullptr != RawFileReaderAr)
	{
		*RawFileReaderAr << RawDataDest;

		RawFileReaderAr->Close();
		delete RawFileReaderAr;
		RawFileReaderAr = nullptr;
	}

	//UE_LOG(LogTemp, Log, TEXT("이름 : %s, 순서 : %d"), *RawDataDest.Name, RawDataDest.Order);


	/* 언리얼 오브젝트 Read & Write  ------------------------------------------------------------*/
	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("오트"));
	StudentSrc->SetOrder(2);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsoultePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsoultePath);

		/* 1. 메모리에 쓰기 ------------------------------------------------------------*/
		// Byte Stream은 언리얼 엔진에서 아래의 버퍼를 사용
		TArray<uint8> BufferArray;

		// 사용할 Memory Writer선언 후 쓰기
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);

		/* 2. File로 저장하기 ------------------------------------------------------------*/
		// 편의성을 위해 스마트 포인터 사용
		// 유니크 포인터를 선언한 로직을 벗어났을 경우 알아서 메모리가 해제됨.
		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsoultePath)))
		{
			// 메모리에 저장되어 있는 데이터를 파일에 쓴 후 ★파일 닫기★
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		/* 3. 저장된 File을 다시 Memory에 읽기 ------------------------------------------------------------*/
		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsoultePath)))
		{
			// 파일의 내용이 버퍼에 담김
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		// 읽는 방식 또한 같다.
		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);

		//UE_LOG(LogTemp, Log, TEXT("[UObject]이름 : %s, 순서 : %d"), *StudentDest->GetName(), StudentDest->GetOrder());
	}

	//#include "JsonObjectConverter.h" 헤더 필요!!!!!
	/* Json Read & Write  ------------------------------------------------------------*/
	{
		const FString JsonDataFileName(TEXT("JsonData.txt"));
		FString JsonDataAbsoultePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsoultePath);

		/* 1. JsonObject로 변환 ------------------------------------------------------------*/
		// 언리얼 오브젝트 -> JsonObject로 변환
		// NotNull을 보장하기 때문에 생성과 동시에 메모리를 할당해주어야 함.
		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();

		// UObject또한 결국 UStruct를 상속받아서 만들기 때문에, UStruct를 JsonObject으로 변환한다.
		// 스키마 정보(데이터의 형식과 필드 정의) / 오브젝트 포인터 / JsonObject 포인터
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);

		/* 2. JsonObject -> File로 쓰기 -----------------------------------------------------*/
		// Json으로 쓰는 Archive 생성
		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);

		// JsonOjbect , JsonArchive
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			// Json이 문자열 형태로 잘 만들어 졌을 것.
			// 해당 함수는 인코딩을 신경쓰지 않아도 운영체제에 잘 저장해줌.
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsoultePath);
		}

		/* 3. File -> JsonReader-> 오브젝트로 읽기--------------------------------------------*/
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsoultePath);

		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		// 문자열이 제대로 생성되지 않을 경우 Null이 들어갈 수 있기 때문에 Ptr로 생성
		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			UStudent* JsonStudentDest = NewObject<UStudent>();
			// JsonObject의 SharedRef 타입 , CDO , UStruct
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				UE_LOG(LogTemp, Log, TEXT("[Json]이름 : %s, 순서 : %d"), *JsonStudentDest->GetName(), JsonStudentDest->GetOrder());
			}
		}
	}
}
