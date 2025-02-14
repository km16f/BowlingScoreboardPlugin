// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/GridSlot.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreBoardActor.h"
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

    CloseButton->OnClicked.AddDynamic(this, &UScoreBoardWidget::OnCloseButtonClicked);
    ResetButton->OnClicked.AddDynamic(this, &UScoreBoardWidget::OnResetButtonClicked);
    
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

                HandleTextBox(CurrentIterationBox, currentColumn, currentRow);

                if (currentColumn == 0 && currentRow == 1 && currentSubFrame == 1)
                {
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
        else if (WidgetName.Contains(FString(TEXT("Third"))))
        {
            
            CurrentFrameData->Score3 = IteratedTextBox;
            currentSubFrame = 3;
            CurrentFrameData->Score3->OnTextCommitted.AddDynamic(this, &UScoreBoardWidget::OnTextChanged);
        
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

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }

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

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }

                activeSpare = true;
            }
            else
            {
                currentFrame->FrameNum = currentFrameNum;
                
                subFrameScore = currentVal - '0';  
                currentFrameScore = currentFrameScore + subFrameScore;

                currentFrame->FrameTotalScore = currentFrameScore;
            }

            HandleStrike();
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
        if (currentFrameNum == 10)
        {
            newFrame = currentFrameNum;
            if (currentSubFrame == 2 && CurrentFrameData->activate3rdScore) { currentSubFrame++;}
        }
        else
        {
            newFrame = currentFrameNum + 1;
            currentSubFrame = 1;
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
            LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;
            LastFrame->remainingStrikeThrows--;
            LastFrame->UpdateWidgets();   
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
    FWorldContext* worldContext;
    UWorld* currentWorld;
    TArray<AActor*> ScoreBoardActors;

    worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);

    currentWorld = worldContext->World();
    UE_LOG(LogTemp, Log, TEXT("CLOSE"))
    GEditor->RequestEndPlayMap();
    
    UGameplayStatics::GetAllActorsOfClass(currentWorld, AScoreBoardActor::StaticClass(), ScoreBoardActors);

    for (AActor* currentActor : ScoreBoardActors)
    {
        if (currentActor) { currentActor->Destroy();}
    }
}

void UScoreBoardWidget::ResetWidget()
{
    UE_LOG(LogTemp, Log, TEXT("RESET"));

    for (UFrameData* currentData : FrameList)
    {
        
        currentData->Score1->SetText(FText::FromString(""));
        if (currentData->FrameNum != 1) {currentData->Score1->SetIsReadOnly(true);}
        
        
        currentData->Score2->SetText(FText::FromString(""));
        currentData->Score2->SetIsReadOnly(true);

        currentData->FrameTotalScoreWidget->SetText(FText::FromString(""));

        if (currentData->Score3)
        {
            currentData->Score3->SetText(FText::FromString(""));
            currentData->Score2->SetIsReadOnly(true);
        }
    }
    currentFrameNum = 1;
    currentFrameScore = 0;
    currentSubFrame = 1;

    activeStrike = false;
    activeSpare = false;


    remainingStrikeReps = 0;
    subFrameScore = 0;
}

void UScoreBoardWidget::OnCloseButtonClicked()
{
    CloseWidget();
}

void UScoreBoardWidget::OnResetButtonClicked()
{
    ResetWidget();
}