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

    Warning->SetVisibility(ESlateVisibility::Hidden);                                                       //Hides our warning message for bad inputs

    //Set some default values for our data tracking variables
    currentFrameNum = 1;
    currentSubFrame = 1;
    activeStrike = false;
    activeSpare = false;

    //Connect our buttons to their delegate functions
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


//Function to start the basic GUI setup and tracking elements
void UScoreBoardWidget::SetupWidget()
{
    int32 test = 0;
    //Initialize our list of Frame Objects
    for (int i = 0; i < 10; i++)
    {
        UFrameData* NewFrame = NewObject<UFrameData>(this);
        FrameList.Add(NewFrame);
    }
    ParseChildren(GridPanel);
};


//Function to recursively iterate through the ScoreBoardWidget and store references to each GUI element for later use
void UScoreBoardWidget::ParseChildren(UPanelWidget* TopWidget, int32 column, int32 row)
{
    int32 currentColumn = column;
    int32 currentRow = row;

    for (UWidget* Child : TopWidget->GetAllChildren())
    {
        if (UGridSlot* GridSlot = Cast<UGridSlot>(Child->Slot))                             // Check to ensure that the child we interact with has a grid slot with relevant column and row info and store this info for this loop iteration
        {
            currentColumn = GridSlot->GetColumn();
            currentRow = GridSlot->GetRow();

        }

        if (Child->IsA<UPanelWidget>())                                                     //Check to ensure the child we're interacting with is a Panel. This way we can skip the Panel GUI elements used for design purposes
        {
            UPanelWidget* PanelChild = Cast<UPanelWidget>(Child);
            ParseChildren(PanelChild, currentColumn, currentRow);
        }
        else
        {

            if (Child->GetClass()->GetName() == "EditableTextBox")                                  //If this child is a Text Box we store info on the box and save it to our FrameData object
            {

                UEditableTextBox* CurrentIterationBox = Cast<UEditableTextBox>(Child);

                HandleTextBox(CurrentIterationBox, currentColumn, currentRow);

                if (currentColumn == 0 && currentRow == 1 && currentSubFrame == 1)                  //If we're on the first block of the first frame, enable this frame for editing
                {
                    CurrentTextBox = CurrentIterationBox;
                    currentSubFrame++;
                }

                if (CurrentIterationBox != CurrentTextBox)                                          //Sets all boxes besides the first box as read only
                {
                    CurrentIterationBox->SetIsReadOnly(true);
                }

            }
        }

    }
    currentSubFrame = 1;
}


//Function to iterate through text box object and store references to the relevant pieces in our FrameData object
void UScoreBoardWidget::HandleTextBox(UEditableTextBox* IteratedTextBox, int32 currentColumn, int32 currentRow)
{

    FString WidgetName = IteratedTextBox->GetName();
    UFrameData* CurrentFrameData = FrameList[currentColumn];
    
    //This switch is to split our text boxes up by row. This easily helps us differentiate between which boxes belong to which FrameData variable. Row 1 is frame number. Row 2 is our editable text boxes. Row 3 is for score totals
    switch (currentRow)         
    {

    case 0:

        CurrentFrameData->FrameNum = currentColumn + 1;                                                             //Continue iteration as this row is reserved for frame number

        break;

    case 1:
        if (WidgetName.Contains(FString(TEXT("First"))))                                                            //GUI Text Boxes are named for their position in the box. Attach boxes to relevant FrameData variable
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

//Function called when a EditableTextBox (row 2 of the scoreboard) is edited
void UScoreBoardWidget::OnTextChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    UFrameData* currentFrame;
    TCHAR currentVal;

    if (CommitType == ETextCommit::OnEnter)                                                                         //Run when the text is finished with hitting ENTER
    {
        bool isValidText = isTextValid(NewText);                                                                    //Check to ensure text entered is valid (0-9, x, X, /)

        if (isValidText)                                            
        {

            Warning->SetVisibility(ESlateVisibility::Hidden);                                                           //Hide our warning message

            currentVal = NewText.ToString()[0];

            currentFrame = FrameList[currentFrameNum - 1];                                                              //Get the current FrameData Obj from the Frame List

            currentFrame->PreviousFrame = (currentFrameNum != 1) ? FrameList[currentFrameNum - 2] : nullptr;            //Grab previous frame for total score calculations. If were on the 1st frame we ignore this to avoid Index Error


            if (currentVal == 'X' || currentVal == 'x')                                                             //Functionality for handling Strike inputs
            {
                
                //Set FrameData variables for strike 
                currentFrame->isStrike = true;
                
                subFrameScore = 10;
                currentFrameScore = 10;

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingStrikeThrows = 2                         //This variable is attached to FrameData to keep track of how many future points are added to this frame for a strike. Starts at 2
                currentFrame->isStrike = true;

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }       //Call to activate the 3rd throw if we're on frame 10

                activeStrike = true;                                                        
            }
            else if (currentVal == '/')
            {
                //Set FrameData variables for spare
                currentFrame->isSpare = true;

                subFrameScore = 10 - currentFrameScore;                                             //Gets the current throws value
                currentFrameScore = 10;  

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingSpareThrows = 1;                                         //Keeps track of remaining bonus points for this frame based on spare

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }           //Call to activate the 3rd throw if we're on frame 10

                activeSpare = true;
            }
            else
            {
                currentFrame->FrameNum = currentFrameNum;
                
                subFrameScore = currentVal - '0';                                               //Gets current throw as an int by subtracting from '0' character. Uses ASCII to get value
                currentFrameScore = currentFrameScore + subFrameScore;

                currentFrame->FrameTotalScore = currentFrameScore;                      //Saves the current total score for this frame
            }

            HandleStrike();
            HandleSpare();
            currentFrame->UpdateWidgets();
            UpdateWidget();
        }
        else
        {
            Warning->SetVisibility(ESlateVisibility::Visible);                      //If input is invalid. Throw warning message up.
        }

    }
}


//This function is used to facilitate scoreboard movement to next frame
void UScoreBoardWidget::UpdateWidget()
{
    int32 newFrame;
    int32 newColumn;

    FText scoreText;

    UFrameData* CurrentFrameData;

    CurrentFrameData = FrameList[currentFrameNum - 1];

    if (currentSubFrame == 1 && !CurrentFrameData->isStrike)                                        //If we're on throw 1 and don't get a strike, move to throw 2
    {
        currentSubFrame = 2;
        newFrame = currentFrameNum;

    }
    else
    {
        if (currentFrameNum == 10)                                                                      //10th frame has special behavior
        {
            newFrame = currentFrameNum;                                                                     //NEVER move past frame 10. Many crashes occur
            if (currentSubFrame == 2 && CurrentFrameData->activate3rdScore) { currentSubFrame++;}           //Move to throw/block 3 of frame if activate3rdScore flag is found
        }
        else
        {
            //This code is for moving to the next frame. If we're on throw 2 and not on frame 10, move to next frame
            newFrame = currentFrameNum + 1;                                     
            currentSubFrame = 1;
            currentFrameScore = 0;
        }

    }

    newColumn = newFrame - 1;                                                           //Handle difference between list index and frame number
    CurrentFrameData = FrameList[newColumn];                                            //Get new FrameData object for next frame
    
    //Grabs the text box for the current throw in the frame
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
  
    CurrentTextBox->SetIsReadOnly(false);                                       //Enables textbox for current throw to be enabled
    currentFrameNum = newFrame;                                                 //Set Class wide tracker for current frame number to NEW frame number
}

//Function to handle special behaviors for strikes
//This function essentially looks at the last two Frame Object (as the farthest you can go in frames while still adding to an old strike score is 2 frames)
//Looks at past two frames and adds current throw score to their frame total if needed
void UScoreBoardWidget::HandleStrike()
{
    UFrameData* TwoFramesBehind;
    UFrameData* LastFrame;

    if (currentFrameNum == 1)                                                           //If we're on frame 1 we do nothing
    {
        return;
    }
    else if (currentFrameNum == 2)                                                      //If we're on frame 2 we only check last frame for strike info
    {
        LastFrame = FrameList[currentFrameNum - 2];                     
        if (LastFrame->remainingStrikeThrows > 0)                                       //Check to see if we still have outstanding additions to last frame total for a strike
        {
            LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;        //If we have totals to still add, we add current throw to last frames total
            LastFrame->remainingStrikeThrows--;                                             //Remove one tally from remaining strike additions for tracking
            LastFrame->UpdateWidgets();                                                     //Update the GUI elements of the Frame 

            if (LastFrame->remainingStrikeThrows == 0)
            {
                activeStrike = false;
            }
        }

    }
    else                                                                                //From frame 3 and onward, we track the previous two frames on each throw to add points back to previous strikes
    {
        TwoFramesBehind = FrameList[currentFrameNum - 3];
        LastFrame = FrameList[currentFrameNum - 2];                                     


        if (TwoFramesBehind->remainingStrikeThrows > 0)                                                 //If the frame from 2 frames ago needs strike additions, we add them here
        {
            TwoFramesBehind->FrameTotalScore = TwoFramesBehind->FrameTotalScore + subFrameScore;
            TwoFramesBehind->remainingStrikeThrows--;
            TwoFramesBehind->UpdateWidgets();
        }

        if (LastFrame->remainingStrikeThrows > 0)                                                   //If the fprevious frame needs strike additions, we add them here
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


//Function to check previous frames to see if current throw needs to be added to past frame totals
void UScoreBoardWidget::HandleSpare()
{
    UFrameData* LastFrame;


    if (currentFrameNum == 1)                                                               //Do nothing on frame one
    {
        return;
    }

    LastFrame = FrameList[currentFrameNum - 2];

    if (LastFrame->remainingSpareThrows > 0)                                            //Checks if we need to add current throw to last frame, adds it to total if needed
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

//Checks if user inputted throw value is valid
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

//Called to show Scoreboard widget on startup
void UScoreBoardWidget::ShowWidget()
{
    SetVisibility(ESlateVisibility::Visible);
}

//Function to close the widget and despawn the spawned custom actor
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

//Called to reset scoreboard. Set all text boxes and score totals to empty. Sets future throws as read only
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

//Function triggered when close button is clicked
void UScoreBoardWidget::OnCloseButtonClicked()
{
    CloseWidget();
}

//Function triggered when reset button is clicked
void UScoreBoardWidget::OnResetButtonClicked()
{
    ResetWidget();
}