// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLineModule.h"

#define LOCTEXT_NAMESPACE "FXLineModule"

DEFINE_LOG_CATEGORY(LogXLine);

void FXLineModule::StartupModule()
{
	const FString includeDirectory = FString::Printf(TEXT("%sXLine/Shaders"), *FPaths::ProjectPluginsDir());
    AddShaderSourceDirectoryMapping("/XLine", includeDirectory);
}

void FXLineModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXLineModule, XLine)