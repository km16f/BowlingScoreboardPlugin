// Copyright Epic Games, Inc. All Rights Reserved.

#include "BowlingScoreBoardCommands.h"

#define LOCTEXT_NAMESPACE "FBowlingScoreBoardModule"

void FBowlingScoreBoardCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "BowlingScoreBoard", "Execute BowlingScoreBoard action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
