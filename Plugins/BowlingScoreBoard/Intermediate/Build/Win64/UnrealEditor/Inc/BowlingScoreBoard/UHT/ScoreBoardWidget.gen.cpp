// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BowlingScoreBoard/Public/ScoreBoardWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeScoreBoardWidget() {}

// Begin Cross Module References
BOWLINGSCOREBOARD_API UClass* Z_Construct_UClass_UScoreBoardWidget();
BOWLINGSCOREBOARD_API UClass* Z_Construct_UClass_UScoreBoardWidget_NoRegister();
SLATECORE_API UEnum* Z_Construct_UEnum_SlateCore_ETextCommit();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UGridPanel_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_BowlingScoreBoard();
// End Cross Module References

// Begin Class UScoreBoardWidget Function OnCloseButtonClicked
struct Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UScoreBoardWidget, nullptr, "OnCloseButtonClicked", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UScoreBoardWidget::execOnCloseButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnCloseButtonClicked();
	P_NATIVE_END;
}
// End Class UScoreBoardWidget Function OnCloseButtonClicked

// Begin Class UScoreBoardWidget Function OnResetButtonClicked
struct Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UScoreBoardWidget, nullptr, "OnResetButtonClicked", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UScoreBoardWidget::execOnResetButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnResetButtonClicked();
	P_NATIVE_END;
}
// End Class UScoreBoardWidget Function OnResetButtonClicked

// Begin Class UScoreBoardWidget Function OnTextChanged
struct Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics
{
	struct ScoreBoardWidget_eventOnTextChanged_Parms
	{
		FText NewText;
		TEnumAsByte<ETextCommit::Type> CommitType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewText_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_NewText;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CommitType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::NewProp_NewText = { "NewText", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ScoreBoardWidget_eventOnTextChanged_Parms, NewText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewText_MetaData), NewProp_NewText_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::NewProp_CommitType = { "CommitType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ScoreBoardWidget_eventOnTextChanged_Parms, CommitType), Z_Construct_UEnum_SlateCore_ETextCommit, METADATA_PARAMS(0, nullptr) }; // 1817921380
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::NewProp_NewText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::NewProp_CommitType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UScoreBoardWidget, nullptr, "OnTextChanged", nullptr, nullptr, Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::ScoreBoardWidget_eventOnTextChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::ScoreBoardWidget_eventOnTextChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UScoreBoardWidget::execOnTextChanged)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_NewText);
	P_GET_PROPERTY(FByteProperty,Z_Param_CommitType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnTextChanged(Z_Param_Out_NewText,ETextCommit::Type(Z_Param_CommitType));
	P_NATIVE_END;
}
// End Class UScoreBoardWidget Function OnTextChanged

// Begin Class UScoreBoardWidget
void UScoreBoardWidget::StaticRegisterNativesUScoreBoardWidget()
{
	UClass* Class = UScoreBoardWidget::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnCloseButtonClicked", &UScoreBoardWidget::execOnCloseButtonClicked },
		{ "OnResetButtonClicked", &UScoreBoardWidget::execOnResetButtonClicked },
		{ "OnTextChanged", &UScoreBoardWidget::execOnTextChanged },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UScoreBoardWidget);
UClass* Z_Construct_UClass_UScoreBoardWidget_NoRegister()
{
	return UScoreBoardWidget::StaticClass();
}
struct Z_Construct_UClass_UScoreBoardWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ScoreBoardWidget.h" },
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GridPanel_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Widget Connected Properties\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Widget Connected Properties" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CloseButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResetButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Warning_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ScoreBoardWidget.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GridPanel;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CloseButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResetButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Warning;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UScoreBoardWidget_OnCloseButtonClicked, "OnCloseButtonClicked" }, // 1432534378
		{ &Z_Construct_UFunction_UScoreBoardWidget_OnResetButtonClicked, "OnResetButtonClicked" }, // 462580558
		{ &Z_Construct_UFunction_UScoreBoardWidget_OnTextChanged, "OnTextChanged" }, // 2387464395
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UScoreBoardWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_GridPanel = { "GridPanel", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreBoardWidget, GridPanel), Z_Construct_UClass_UGridPanel_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GridPanel_MetaData), NewProp_GridPanel_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_CloseButton = { "CloseButton", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreBoardWidget, CloseButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CloseButton_MetaData), NewProp_CloseButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_ResetButton = { "ResetButton", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreBoardWidget, ResetButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResetButton_MetaData), NewProp_ResetButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_Warning = { "Warning", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UScoreBoardWidget, Warning), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Warning_MetaData), NewProp_Warning_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UScoreBoardWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_GridPanel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_CloseButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_ResetButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UScoreBoardWidget_Statics::NewProp_Warning,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreBoardWidget_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UScoreBoardWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_BowlingScoreBoard,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreBoardWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UScoreBoardWidget_Statics::ClassParams = {
	&UScoreBoardWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UScoreBoardWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UScoreBoardWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UScoreBoardWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UScoreBoardWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UScoreBoardWidget()
{
	if (!Z_Registration_Info_UClass_UScoreBoardWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UScoreBoardWidget.OuterSingleton, Z_Construct_UClass_UScoreBoardWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UScoreBoardWidget.OuterSingleton;
}
template<> BOWLINGSCOREBOARD_API UClass* StaticClass<UScoreBoardWidget>()
{
	return UScoreBoardWidget::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UScoreBoardWidget);
UScoreBoardWidget::~UScoreBoardWidget() {}
// End Class UScoreBoardWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_ScoreBoardWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UScoreBoardWidget, UScoreBoardWidget::StaticClass, TEXT("UScoreBoardWidget"), &Z_Registration_Info_UClass_UScoreBoardWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UScoreBoardWidget), 3015680372U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_ScoreBoardWidget_h_1131283542(TEXT("/Script/BowlingScoreBoard"),
	Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_ScoreBoardWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_kylem_Documents_Unreal_Projects_BowlingProject_Plugins_BowlingScoreBoard_Source_BowlingScoreBoard_Public_ScoreBoardWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
