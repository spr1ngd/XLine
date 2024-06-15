// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XLine/Public/XLine.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXLine() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_XLine();
	XLINE_API UClass* Z_Construct_UClass_AXLine();
	XLINE_API UClass* Z_Construct_UClass_AXLine_NoRegister();
// End Cross Module References
	void AXLine::StaticRegisterNativesAXLine()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AXLine);
	UClass* Z_Construct_UClass_AXLine_NoRegister()
	{
		return AXLine::StaticClass();
	}
	struct Z_Construct_UClass_AXLine_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AXLine_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_XLine,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AXLine_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "XLine.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/XLine.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AXLine_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AXLine>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AXLine_Statics::ClassParams = {
		&AXLine::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AXLine_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AXLine_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AXLine()
	{
		if (!Z_Registration_Info_UClass_AXLine.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AXLine.OuterSingleton, Z_Construct_UClass_AXLine_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AXLine.OuterSingleton;
	}
	template<> XLINE_API UClass* StaticClass<AXLine>()
	{
		return AXLine::StaticClass();
	}
	AXLine::AXLine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AXLine);
	AXLine::~AXLine() {}
	struct Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLine_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLine_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AXLine, AXLine::StaticClass, TEXT("AXLine"), &Z_Registration_Info_UClass_AXLine, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AXLine), 3838387140U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLine_h_1450558829(TEXT("/Script/XLine"),
		Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLine_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLine_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
