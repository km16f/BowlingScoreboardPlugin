// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BowlingScoreBoard/Public/FrameData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFrameData() {}

// Begin Cross Module References
BOWLINGSCOREBOARD_API UClass* Z_Construct_UClass_UFrameData();
BOWLINGSCOREBOARD_API UClass* Z_Construct_UClass_UFrameData_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_BowlingScoreBoard();
// End Cross Module References

// Begin Class UFrameData
void UFrameData::StaticRegisterNativesUFrameData()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFrameData);
UClass* Z_Construct_UClass_UFrameData_NoRegister()
{
	return UFrameData::StaticClass();
}
struct Z_Construct_UClass_UFrameData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "FrameData.h" },
		{ "ModuleRelativePath", "Public/FrameData.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFrameData>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UFrameData_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_BowlingScoreBoard,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFrameData_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFrameData_Statics::ClassParams = {
	&UFrameData::StaticClass,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFrameData_Statics::Class_MetaDataParams), Z_Construct_UClass_UFrameData_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UFrameData()
{
	if (!Z_Registration_Info_UClass_UFrameData.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFrameData.OuterSingleton, Z_Construct_UClass_UFrameData_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFrameData.OuterSingleton;
}
template<> BOWLINGSCOREBOARD_API UClass* StaticClass<UFrameData>()
{
	return UFrameData::StaticClass();
}
UFrameData::UFrameData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UFrameData);
UFrameData::~UFrameData() {}
// End Class UFrameData

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_FrameData_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFrameData, UFrameData::StaticClass, TEXT("UFrameData"), &Z_Registration_Info_UClass_UFrameData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFrameData), 2629081353U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_FrameData_h_4245426208(TEXT("/Script/BowlingScoreBoard"),
	Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_FrameData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_FrameData_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
