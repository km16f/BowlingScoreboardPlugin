// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameData.h"


//Function for taking all data stored in UFrameData object and updating the relevant GUI elements accordingly
void UFrameData::UpdateWidgets()
{
	int32 PrevRunningTotal;
	FText ScoreText;

	if (isStrike)													//If the current frame is a strike we need to move to the next frame and ignore next block in this frame
	{
		ScoreText = FText::FromString("_");
		Score2->SetIsReadOnly(false);
		Score2->SetText(ScoreText);
	}

	PrevRunningTotal = (PreviousFrame == nullptr) ? 0 : PreviousFrame->RunningBoardTotal;               //This statement manages the first frame to avoid a SEG FAULT and crashing Unreal by acessing non existing list index

	RunningBoardTotal = PrevRunningTotal + FrameTotalScore;

	ScoreText = FText::AsNumber(RunningBoardTotal);
	FrameTotalScoreWidget->SetText(ScoreText);															//Sets the current total score for this frame
}