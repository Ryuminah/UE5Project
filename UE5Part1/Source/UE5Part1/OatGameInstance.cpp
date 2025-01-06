// Fill out your copyright notice in the Description page of Project Settings.

#include "OatGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "StudentManager.h"
#include "Algo/Accumulate.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

// 언리얼 엔진 프로젝트의 고유한 경로 중 하나
// /Game -> 게임에서 사용되는 에셋들을 모아놓은 대표 폴더
// /Saved -> /Temp에 맵핑

const FString UOatGameInstance::PackageName = TEXT("/Game/Student");
// Student 패키지가 메인으로 관리할 에셋 이름
const FString UOatGameInstance::AssetName = TEXT("TopStudent");


UOatGameInstance::UOatGameInstance()
{
	// 게임 시작 전 미리 메모리에 올라와 있어야 하는 에셋을 생성자에서 로드
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(*TopSoftObjectPath);
	
	// 로딩 여부 확인
	if (UASSET_TopStudent.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("[Constructor Load]이름 : %s, 순서 : %d"), *UASSET_TopStudent.Object->GetName(), UASSET_TopStudent.Object->GetOrder());
	}
}

void UOatGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(TEXT("오트"), 1);
	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));

	/* 일반 c++ 구조체 ----------------------------------------------------------------*/
	{
		/* 1. 경로 생성 ---------------------------------------------------------------*/
		// 언리얼 프로젝트 내의 Saved 폴더의 경로를 얻어올 수 있음.
		//UE_LOG(LogTemp, Log, TEXT("%s"), *SavedDir);

		// 저장할 파일 이름 지정
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 파일에 대한 절대경로 값
		FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *RawDataAbsolutePath);
		// 경로 정리
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *RawDataAbsolutePath);

		/* 2. 파일 데이터 쓰기 ---------------------------------------------------------*/
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
	}
	//UE_LOG(LogTemp, Log, TEXT("이름 : %s, 순서 : %d"), *RawDataDest.Name, RawDataDest.Order);

	/* 언리얼 오브젝트 Read & Write  ---------------------------------------------------*/
	{
		StudentSrc = NewObject<UStudent>();
		StudentSrc->SetName(TEXT("오트"));
		StudentSrc->SetOrder(2);

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
				//UE_LOG(LogTemp, Log, TEXT("[Json]이름 : %s, 순서 : %d"), *JsonStudentDest->GetName(), JsonStudentDest->GetOrder());
			}
		}
	}

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();
	/* 비동기 방식의 에셋 로딩 ------------------------------------------------------------*/
	{
		const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
		Handle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath,
			[&]()
			{
				if (Handle.IsValid() && Handle->HasLoadCompleted())
				{
					UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
					if (TopStudent)
					{
						UE_LOG(LogTemp, Log, TEXT("[Async Load]이름 : %s, 순서 : %d"), *TopStudent->GetName(), TopStudent->GetOrder());
						Handle->ReleaseHandle();
					}
				}
			}
		);
	}
}

void UOatGameInstance::SaveStudentPackage() const
{
	// 이미 패키지가 존재할 경우 전부 로딩 후 저장하는 것이 좋다.
	/* 1. 패키지 생성 ------------------------------------------------------------*/
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}
	else
	{
		StudentPackage = CreatePackage(*PackageName);
	}

	// 패키지 저장하는 옵션 관련 플래그 (일반적인 저장 방식)
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	// 인자가 아무것도 없을 경우 Transient Package안에 임시로 저장
	// Package , CDO, AssetName , ObjectFlag
	UStudent* TopStudent = NewObject<UStudent>(StudentPackage, UStudent::StaticClass(), *AssetName, ObjectFlag);
	TopStudent->SetName(TEXT("오트"));
	TopStudent->SetOrder(211227);

	// TopStudent에 대하여 SubObject 생성
	const int32 NumOfSubs = 10;
	for (int32 i = 1; i <= 10; ++i)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"), i);
		// 패키지의 에셋인 TopStudent 하위로 SubObject가 들어가야 함.
		UStudent* SubStudent = NewObject<UStudent>(TopStudent, UStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("학생_%d"), i));
		SubStudent->SetOrder(i);
	}
	
	// 6. 에셋을 레지스트리에 등록
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().AssetCreated(TopStudent);
	StudentPackage->MarkPackageDirty();

	/* 2. 패키지 저장 ------------------------------------------------------------*/
	// 패키지가 저장될 경로 지정 및 확장자 부여
	// 프로젝트 정보를 바탕으로 현재 프로젝트의 Content폴더 지정 -> PakcageName이 확장자가 됨 -> .uasset확장자
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	// #include "UObject/SavePackage"
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	// Package, UObject(이미 앞에서 패키지-에셋을 엮어줬기 때문에 필요 X) , FileName , 저장 관련 파라미터
	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		// 콘텐츠 브라우저 강제 갱신
		AssetRegistryModule.Get().ScanModifiedAssetFiles({ PackageFileName });
		UE_LOG(LogTemp, Log, TEXT("패키지 저장 완료"));
	}
}

void UOatGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (nullptr == StudentPackage)
	{
		UE_LOG(LogTemp, Warning, TEXT("패키지가 존재하지 않습니다"));
		return;
	}

	// 에셋을 전부 로드
	StudentPackage->FullyLoad();

	// 패키지 내부에서 UStudentType의 언리얼 오브젝트를 찾아 반환시켜줌
	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	UE_LOG(LogTemp, Log, TEXT("[Asset Load]이름 : %s, 순서 : %d"), *TopStudent->GetName(), TopStudent->GetOrder());
}

void UOatGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 패키지 로딩이 아니기 때문에 null을 넣어줌 , 경로 정보
	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);
	UE_LOG(LogTemp, Log, TEXT("[Object Load]이름 : %s, 순서 : %d"), *TopStudent->GetName(), TopStudent->GetOrder());
}
