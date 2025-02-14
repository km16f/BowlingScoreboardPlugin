// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "BowlingScoreBoardStyle.h"

class FBowlingScoreBoardCommands : public TCommands<FBowlingScoreBoardCommands>
{
public:

	FBowlingScoreBoardCommands()
		: TCommands<FBowlingScoreBoardCommands>(TEXT("BowlingScoreBoard"), NSLOCTEXT("Contexts", "BowlingScoreBoard", "BowlingScoreBoard Plugin"), NAME_None, FBowlingScoreBoardStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
