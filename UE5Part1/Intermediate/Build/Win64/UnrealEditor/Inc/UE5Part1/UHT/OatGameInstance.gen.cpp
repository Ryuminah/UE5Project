// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UE5Part1/OatGameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOatGameInstance() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
UE5PART1_API UClass* Z_Construct_UClass_UOatGameInstance();
UE5PART1_API UClass* Z_Construct_UClass_UOatGameInstance_NoRegister();
UPackage* Z_Construct_UPackage__Script_UE5Part1();
// End Cross Module References

// Begin Class UOatGameInstance
void UOatGameInstance::StaticRegisterNativesUOatGameInstance()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOatGameInstance);
UClass* Z_Construct_UClass_UOatGameInstance_NoRegister()
{
	return UOatGameInstance::StaticClass();
}
struct Z_Construct_UClass_UOatGameInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "OatGameInstance.h" },
		{ "ModuleRelativePath", "OatGameInstance.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOatGameInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UOatGameInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_UE5Part1,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOatGameInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UOatGameInstance_Statics::ClassParams = {
	&UOatGameInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOatGameInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UOatGameInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UOatGameInstance()
{
	if (!Z_Registration_Info_UClass_UOatGameInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UOatGameInstance.OuterSingleton, Z_Construct_UClass_UOatGameInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UOatGameInstance.OuterSingleton;
}
template<> UE5PART1_API UClass* StaticClass<UOatGameInstance>()
{
	return UOatGameInstance::StaticClass();
}
UOatGameInstance::UOatGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UOatGameInstance);
UOatGameInstance::~UOatGameInstance() {}
// End Class UOatGameInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_SourceTree_Clone_UE5Project_UE5Part1_Source_UE5Part1_OatGameInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UOatGameInstance, UOatGameInstance::StaticClass, TEXT("UOatGameInstance"), &Z_Registration_Info_UClass_UOatGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOatGameInstance), 3101977801U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SourceTree_Clone_UE5Project_UE5Part1_Source_UE5Part1_OatGameInstance_h_383309108(TEXT("/Script/UE5Part1"),
	Z_CompiledInDeferFile_FID_SourceTree_Clone_UE5Project_UE5Part1_Source_UE5Part1_OatGameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SourceTree_Clone_UE5Project_UE5Part1_Source_UE5Part1_OatGameInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
