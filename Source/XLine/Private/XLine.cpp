// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLine.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FXLineModule"

DEFINE_LOG_CATEGORY(LogXLine);

void FXLineModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("XLine"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin/XLine"), PluginShaderDir);
}

void FXLineModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXLineModule, XLine)