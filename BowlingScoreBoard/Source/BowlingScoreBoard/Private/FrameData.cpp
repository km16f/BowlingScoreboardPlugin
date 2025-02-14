// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameData.h"

void UFrameData::UpdateWidgets()
{
	int32 PrevRunningTotal;
	FText ScoreText;

	if (isStrike)
	{
		ScoreText = FText::FromString("_");
		Score2->SetIsReadOnly(false);
		Score2->SetText(ScoreText);
	}

	PrevRunningTotal = (PreviousFrame == nullptr) ? 0 : PreviousFrame->RunningBoardTotal;

	UE_LOG(LogTemp, Log, TEXT("PREV TOTAL: %d"), PrevRunningTotal);

	RunningBoardTotal = PrevRunningTotal + FrameTotalScore;

	UE_LOG(LogTemp, Log, TEXT("RUN TOTAL: %d"), RunningBoardTotal);
	ScoreText = FText::AsNumber(RunningBoardTotal);
	FrameTotalScoreWidget->SetText(ScoreText);
}