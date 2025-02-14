// Copyright Epic Games, Inc. All Rights Reserved.

#include "BowlingScoreBoardStyle.h"
#include "BowlingScoreBoard.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FBowlingScoreBoardStyle::StyleInstance = nullptr;

void FBowlingScoreBoardStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBowlingScoreBoardStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FBowlingScoreBoardStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BowlingScoreBoardStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FBowlingScoreBoardStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("BowlingScoreBoardStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BowlingScoreBoard")->GetBaseDir() / TEXT("Resources"));

	Style->Set("BowlingScoreBoard.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FBowlingScoreBoardStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBowlingScoreBoardStyle::Get()
{
	return *StyleInstance;
}
