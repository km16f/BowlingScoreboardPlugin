// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameData.h"

//Function to update GUI elements for the frame based on Frame Data properties
void UFrameData::UpdateWidgets()
{
	int32 PrevRunningTotal;
	FText ScoreText;

	//If a strike is bowled, set frame 2 to "_" and move on
	if (isStrike)
	{
		ScoreText = FText::FromString("_");
		Score2->SetIsReadOnly(false);
		Score2->SetText(ScoreText);
	}

	PrevRunningTotal = (PreviousFrame == nullptr) ? 0 : PreviousFrame->RunningBoardTotal;										//If we're on the first frame, the total is 0

	UE_LOG(LogTemp, Log, TEXT("PREV TOTAL: %d"), PrevRunningTotal);

	RunningBoardTotal = PrevRunningTotal + FrameTotalScore;																		//Calculate current total

	UE_LOG(LogTemp, Log, TEXT("RUN TOTAL: %d"), RunningBoardTotal);
	ScoreText = FText::AsNumber(RunningBoardTotal);
	FrameTotalScoreWidget->SetText(ScoreText);																					//Set the total score in the widget
}