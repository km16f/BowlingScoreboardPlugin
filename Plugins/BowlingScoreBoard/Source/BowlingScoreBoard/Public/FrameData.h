// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "UObject/NoExportTypes.h"
#include "FrameData.generated.h"

/**
 *  This is a data object to represent a single frame in the scoreboard
 * 
 *  This class is used to track frame info and connect to the Frame's text boxes
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

	//Used to track remining bonus throws added on for strikes and spares
	int32 remainingStrikeThrows;
	int32 remainingSpareThrows;

	//Tracking score information
	int32 FrameTotalScore;
	int32 FrameNum;
	int32 RunningBoardTotal = 0;

	//Traccks the text boxes for this frame
	UEditableTextBox* Score1;
	UEditableTextBox* Score2;
	UEditableTextBox* Score3;
	UEditableTextBox* FrameTotalScoreWidget;

	//Track the previous frame in order to calculate totals
	UFrameData* PreviousFrame;
	
};
