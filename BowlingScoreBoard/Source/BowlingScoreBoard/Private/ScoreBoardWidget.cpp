// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/GridSlot.h"
#include "WidgetBlueprint.h"

UScoreBoardWidget::UScoreBoardWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UScoreBoardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Warning->SetVisibility(ESlateVisibility::Hidden);

    currentFrameNum = 1;
    currentSubFrame = 1;
    activeStrike = false;
    activeSpare = false;

    

    UE_LOG(LogTemp, Log, TEXT("CONSTRUCT"));
    
    if (!GridPanel)
    {
        UE_LOG(LogTemp, Log, TEXT("Error: CANT FOUND OUR GRIDPANEL"));
    }
    else
    {
        SetupWidget();
    }
}

void UScoreBoardWidget::SetupWidget()
{
    int32 test = 0;
    for (int i = 0; i < 10; i++)
    {
        UFrameData* NewFrame = NewObject<UFrameData>(this);
        FrameList.Add(NewFrame);
    }
    for (UFrameData* Temp : FrameList)
    {
        UE_LOG(LogTemp, Log, TEXT("Iteration NUM: %d"), test);
        test++;
    }
    ParseChildren(GridPanel);
};


void UScoreBoardWidget::ParseChildren(UPanelWidget* TopWidget, int32 column, int32 row)
{
    int32 currentColumn = column;
    int32 currentRow = row;

    for (UWidget* Child : TopWidget->GetAllChildren())
    {
        if (UGridSlot* GridSlot = Cast<UGridSlot>(Child->Slot))
        {
            currentColumn = GridSlot->GetColumn();
            currentRow = GridSlot->GetRow();

        }

        if (Child->IsA<UPanelWidget>())
        {
            UPanelWidget* PanelChild = Cast<UPanelWidget>(Child);
            ParseChildren(PanelChild, currentColumn, currentRow);
        }
        else
        {

            if (Child->GetClass()->GetName() == "EditableTextBox")
            {

                UEditableTextBox* CurrentIterationBox = Cast<UEditableTextBox>(Child);
                UE_LOG(LogTemp, Log, TEXT("COL: %d"), currentColumn);
                UE_LOG(LogTemp, Log, TEXT("Row: %d"), currentRow);
                UE_LOG(LogTemp, Log, TEXT("CURRENT SUB FRAME: %d"), currentSubFrame);

                HandleTextBox(CurrentIterationBox, currentColumn, currentRow);

                if (currentColumn == 0 && currentRow == 1 && currentSubFrame == 1)
                {
                    UE_LOG(LogTemp, Log, TEXT("WHY IT NO WORK"));
                    CurrentTextBox = CurrentIterationBox;
                    currentSubFrame++;
                }

                if (CurrentIterationBox != CurrentTextBox)
                {
                    CurrentIterationBox->SetIsReadOnly(true);
                }

            }
        }

    }
    currentSubFrame = 1;
}



void UScoreBoardWidget::HandleTextBox(UEditableTextBox* IteratedTextBox, int32 currentColumn, int32 currentRow)
{

    FString WidgetName = IteratedTextBox->GetName();
    UFrameData* CurrentFrameData = FrameList[currentColumn];
    

    switch (currentRow)
    {

    case 0:

        CurrentFrameData->FrameNum = currentColumn + 1;

        break;

    case 1:
        if (WidgetName.Contains(FString(TEXT("First"))))
        {
            CurrentFrameData->Score1 = IteratedTextBox;
            currentSubFrame = 1;
            CurrentFrameData->Score1->OnTextCommitted.AddDynamic(this, &UScoreBoardWidget::OnTextChanged);
        }
        else if (WidgetName.Contains(FString(TEXT("Second"))))
        {
            CurrentFrameData->Score2 = IteratedTextBox;
            currentSubFrame = 2;
            CurrentFrameData->Score2->OnTextCommitted.AddDynamic(this, &UScoreBoardWidget::OnTextChanged);
        }
        else
        {
            if (currentColumn == 3)
            {
                CurrentFrameData->Score3 = IteratedTextBox;
                currentSubFrame = 3;
                CurrentFrameData->Score3->OnTextCommitted.AddDynamic(this, &UScoreBoardWidget::OnTextChanged);
            }
        }
        break;

    case 2:

        CurrentFrameData->FrameTotalScoreWidget = IteratedTextBox;
        break;

    }
}


void UScoreBoardWidget::OnTextChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    UFrameData* currentFrame;
    TCHAR currentVal;

    if (CommitType == ETextCommit::OnEnter) 
    {
        bool isValidText = isTextValid(NewText);

        if (isValidText)        
        {
            Warning->SetVisibility(ESlateVisibility::Hidden);

            currentVal = NewText.ToString()[0];

            currentFrame = FrameList[currentFrameNum - 1];

            currentFrame->PreviousFrame = (currentFrameNum != 1) ? FrameList[currentFrameNum - 2] : nullptr;


            if (currentVal == 'X' || currentVal == 'x')
            {
                
                currentFrame->isStrike = true;
                
                subFrameScore = 10;
                currentFrameScore = 10;

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingStrikeThrows = 2;
                currentFrame->isStrike = true;

                activeStrike = true;
            }
            else if (currentVal == '/')
            {
                currentFrame->isSpare = true;

                subFrameScore = 10 - currentFrameScore;
                currentFrameScore = 10;  

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingSpareThrows = 1;

                activeSpare = true;
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("CURRENT FRAME: %d"), currentFrameNum);
                currentFrame->FrameNum = currentFrameNum;
                
                subFrameScore = currentVal - '0';  
                currentFrameScore = currentFrameScore + subFrameScore;

                currentFrame->FrameTotalScore = currentFrameScore;
            }

            HandleStrike();
            HandleSpare();
            HandleSpare();
            currentFrame->UpdateWidgets();
            UpdateWidget();
        }
        else
        {
            Warning->SetVisibility(ESlateVisibility::Visible);
        }

    }
}

int32 UScoreBoardWidget::CalculateTotal()
{
    //int32 runningTotal;


    totalScore = subFrameScore + totalScore;

    return totalScore;
}

void UScoreBoardWidget::UpdateWidget()
{
    int32 newFrame;
    int32 newColumn;

    FText scoreText;

    UFrameData* CurrentFrameData;

    CurrentFrameData = FrameList[currentFrameNum - 1];

    if (currentSubFrame == 1 && !CurrentFrameData->isStrike)
    {
        currentSubFrame = 2;
        newFrame = currentFrameNum;

    }
    else
    {
        currentSubFrame = (currentFrameNum == 10 && currentFrameScore == 10) ? 3 : 1;

        if (currentFrameNum == 10 && currentFrameScore == 10)
        {
            newFrame = currentFrameNum;
        }
        else
        {
            newFrame = currentFrameNum + 1;
            currentFrameScore = 0;
        }

    }

    newColumn = newFrame - 1;
    CurrentFrameData = FrameList[newColumn];
    

    if (currentSubFrame == 1)
    {
        CurrentTextBox = CurrentFrameData->Score1;
    }
    else if (currentSubFrame == 2)
    {
        CurrentTextBox = CurrentFrameData->Score2;
    }
    else
    {
        CurrentTextBox = CurrentFrameData->Score3;
    }
  
    CurrentTextBox->SetIsReadOnly(false);;
    bool test = FSlateApplication::Get().SetKeyboardFocus(CurrentTextBox->GetCachedWidget(), EFocusCause::SetDirectly);
    CurrentTextBox->SetKeyboardFocus();
    currentFrameNum = newFrame;
}

void UScoreBoardWidget::HandleStrike()
{
    UFrameData* TwoFramesBehind;
    UFrameData* LastFrame;

    if (currentFrameNum == 1) 
    {
        return;
    }
    else if (currentFrameNum == 2)
    {
        LastFrame = FrameList[currentFrameNum - 2];
        if (LastFrame->remainingStrikeThrows > 0)
        {
            LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;
            LastFrame->remainingStrikeThrows--;
            LastFrame->UpdateWidgets();

            if (LastFrame->remainingStrikeThrows == 0)
            {
                activeStrike = false;
            }
        }

    }
    else 
    {
        TwoFramesBehind = FrameList[currentFrameNum - 3];
        LastFrame = FrameList[currentFrameNum - 2];

        

        if (TwoFramesBehind->remainingStrikeThrows > 0)
        {
            TwoFramesBehind->FrameTotalScore = TwoFramesBehind->FrameTotalScore + subFrameScore;
            TwoFramesBehind->remainingStrikeThrows--;
            TwoFramesBehind->UpdateWidgets();
        }

        if (LastFrame->remainingStrikeThrows > 0)
        {
            UE_LOG(LogTemp, Log, TEXT("FRAME TOTAL Before: %d"), LastFrame->FrameTotalScore);
            LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;
            LastFrame->remainingStrikeThrows--;
            LastFrame->UpdateWidgets();
            UE_LOG(LogTemp, Log, TEXT("THROWS LEFT: %d"), LastFrame->remainingStrikeThrows);
            UE_LOG(LogTemp, Log, TEXT("SUB FRAME SCORE: %d"), subFrameScore);
            UE_LOG(LogTemp, Log, TEXT("FRAME TOTAL AFTER: %d"), LastFrame->FrameTotalScore);
            
        }

        if (TwoFramesBehind->remainingStrikeThrows == 0 && LastFrame->remainingStrikeThrows == 0)
        {
            activeStrike = false;
        }
    }

}

void UScoreBoardWidget::HandleSpare()
{
    UFrameData* LastFrame;


    if (currentFrameNum == 1)
    {
        return;
    }

    LastFrame = FrameList[currentFrameNum - 2];

    if (LastFrame->remainingSpareThrows > 0)
    {
        LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;
        LastFrame->remainingSpareThrows--;
        LastFrame->UpdateWidgets();
    }

    if (LastFrame->remainingSpareThrows == 0)
    {
        activeSpare = false;
    }

}

bool UScoreBoardWidget::isTextValid(const FText& NewText)
{
    FString StringValue = NewText.ToString();

    if (StringValue.Len() == 1)
    {
        TCHAR textChar = StringValue[0];
        if (FChar::IsDigit(textChar))
        {
            int32 number = textChar - '0';
            if (number >= 0 && number <= 9)
            {
                return true;
            }
        }
        else if (textChar == 'X' || textChar == 'x' || textChar == '/')
        {
            return true;
        }
    }
    return false;
}

void UScoreBoardWidget::ShowWidget()
{
    SetVisibility(ESlateVisibility::Visible);
}

void UScoreBoardWidget::CloseWidget()
{
    SetVisibility(ESlateVisibility::Hidden);
}