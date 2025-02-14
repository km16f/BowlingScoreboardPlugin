// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "UObject/NoExportTypes.h"
#include "FrameData.generated.h"

/**
 * Custom Data class being used to track each frame of the bowling scoreboard and the various GUI elements attached to each frame
 * 
 * This class is neccessary for easy traversal of the scoreboard and for the Reset button
 */
UCLASS()
class BOWLINGSCOREBOARD_API UFrameData : public UObject
{
	GENERATED_BODY()

public:

	void UpdateWidgets();

	bool isStrike;
	bool isSpare;
	bool activate3rdScore;

	//Used to track progress on calculating total additional points for Strikes and Spares
	int32 remainingStrikeThrows;
	int32 remainingSpareThrows;

	//Tracks basic information for the current frame
	int32 FrameTotalScore;
	int32 FrameNum;
	int32 RunningBoardTotal = 0;

	//Track the 3 possible Score Text Boxes
	UEditableTextBox* Score1;
	UEditableTextBox* Score2;
	UEditableTextBox* Score3;

	//Total score widget displayed at the bottom row of the scoreboard
	UEditableTextBox* FrameTotalScoreWidget;

	//Need to track the previous Frame in order for accurate score totals
	UFrameData* PreviousFrame;
	
};
