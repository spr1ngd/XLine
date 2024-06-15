// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XLine/Public/XLineComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeXLineComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent();
	UPackage* Z_Construct_UPackage__Script_XLine();
	XLINE_API UClass* Z_Construct_UClass_UXLineComponent();
	XLINE_API UClass* Z_Construct_UClass_UXLineComponent_NoRegister();
// End Cross Module References
	void UXLineComponent::StaticRegisterNativesUXLineComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UXLineComponent);
	UClass* Z_Construct_UClass_UXLineComponent_NoRegister()
	{
		return UXLineComponent::StaticClass();
	}
	struct Z_Construct_UClass_UXLineComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UXLineComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UStaticMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_XLine,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UXLineComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HideCategories", "Object Activation Components|Activation Trigger" },
		{ "IncludePath", "XLineComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/XLineComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UXLineComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UXLineComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UXLineComponent_Statics::ClassParams = {
		&UXLineComponent::StaticClass,
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
		0x00A010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UXLineComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UXLineComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UXLineComponent()
	{
		if (!Z_Registration_Info_UClass_UXLineComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UXLineComponent.OuterSingleton, Z_Construct_UClass_UXLineComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UXLineComponent.OuterSingleton;
	}
	template<> XLINE_API UClass* StaticClass<UXLineComponent>()
	{
		return UXLineComponent::StaticClass();
	}
	UXLineComponent::UXLineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UXLineComponent);
	UXLineComponent::~UXLineComponent() {}
	struct Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLineComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLineComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UXLineComponent, UXLineComponent::StaticClass, TEXT("UXLineComponent"), &Z_Registration_Info_UClass_UXLineComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UXLineComponent), 2301125767U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLineComponent_h_3545786505(TEXT("/Script/XLine"),
		Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLineComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_thing_ue5_Plugins_XLine_Source_XLine_Public_XLineComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
