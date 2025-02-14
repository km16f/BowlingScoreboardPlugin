// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "UObject/NoExportTypes.h"
#include "FrameData.generated.h"

/**
 * 
 */
UCLASS()
class BOWLINGSCOREBOARD_API UFrameData : public UObject
{
	GENERATED_BODY()

public:

	void UpdateWidgets();

	bool isStrike;
	bool isSpare;

	int32 remainingStrikeThrows;
	int32 remainingSpareThrows;

	int32 FrameTotalScore;
	int32 FrameNum;
	int32 RunningBoardTotal = 0;

	UEditableTextBox* Score1;
	UEditableTextBox* Score2;
	UEditableTextBox* Score3;

	UEditableTextBox* FrameTotalScoreWidget;

	UFrameData* PreviousFrame;
	
};
