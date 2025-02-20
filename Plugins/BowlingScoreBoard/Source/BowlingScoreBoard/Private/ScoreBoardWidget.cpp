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


//Constructor sets up default values 
void UScoreBoardWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Warning->SetVisibility(ESlateVisibility::Hidden);                                                                                   //Hide our error message by default

    currentFrameNum = 1;
    currentSubFrame = 1;
    activeStrike = false;
    activeSpare = false;

    //Connect our event handler delegates
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


//Sets up our Frame Objects and parses through GUI elements to attach them to trackable references
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

//Recursive function to iterate through the GUI elements of the widget to grab the text box objects and attach them to the Frame Data object for referencing later
void UScoreBoardWidget::ParseChildren(UPanelWidget* TopWidget, int32 column, int32 row)
{
    int32 currentColumn = column;
    int32 currentRow = row;

    for (UWidget* Child : TopWidget->GetAllChildren())
    {
        if (UGridSlot* GridSlot = Cast<UGridSlot>(Child->Slot))
        {
            currentColumn = GridSlot->GetColumn();                                                                              //Track the current row and column of the element we're on
            currentRow = GridSlot->GetRow();

        }

        if (Child->IsA<UPanelWidget>())                                                                                     //If the current GUI element is a panel we recursively call our function to find the text boxes attached to it
        {
            UPanelWidget* PanelChild = Cast<UPanelWidget>(Child);
            ParseChildren(PanelChild, currentColumn, currentRow);
        }
        else
        {

            if (Child->GetClass()->GetName() == "EditableTextBox")                                                          //Found a text box we need to track
            {

                UEditableTextBox* CurrentIterationBox = Cast<UEditableTextBox>(Child);                                      //Get the object as a text box 

                HandleTextBox(CurrentIterationBox, currentColumn, currentRow);

                if (currentColumn == 0 && currentRow == 1 && currentSubFrame == 1)                                          //Set some values up for the initialization of the first shot on the first frame
                {
                    CurrentTextBox = CurrentIterationBox;
                    currentSubFrame++;
                }

                if (CurrentIterationBox != CurrentTextBox)                                                                  //Set all other shot boxes as uneditable
                {
                    CurrentIterationBox->SetIsReadOnly(true);
                }

            }
        }

    }
    currentSubFrame = 1;
}


//Function to handle the text box widgets found in our ScoreBoard widget
//This function tracks the text boxes found in row 1, since these are the editable text boxes
void UScoreBoardWidget::HandleTextBox(UEditableTextBox* IteratedTextBox, int32 currentColumn, int32 currentRow)
{

    FString WidgetName = IteratedTextBox->GetName();
    UFrameData* CurrentFrameData = FrameList[currentColumn];
    

    switch (currentRow)
    {

    case 0:                                                                                                         //Row 0 is reserved for the frame number

        CurrentFrameData->FrameNum = currentColumn + 1;

        break;

    case 1:                                                                                                                 //Row 1 is for the editable text boxes where scores will be entered
        if (WidgetName.Contains(FString(TEXT("First"))))                                                                    //Text box GUI elements are named for their location in the frame
        {
            CurrentFrameData->Score1 = IteratedTextBox;                                                                     //Save reference for TextBox object to the current FrameData object
            currentSubFrame = 1;
            CurrentFrameData->Score1->OnTextCommitted.AddDynamic(this, &UScoreBoardWidget::OnTextChanged);                  //Connect event handler to be called when text is typed and the "enter" button is hit
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

        CurrentFrameData->FrameTotalScoreWidget = IteratedTextBox;                                                          //Save reference to the total score Text Box for this Frame
        break;

    }
}

//This function is called when a user enters a score and presses enter
void UScoreBoardWidget::OnTextChanged(const FText& NewText, ETextCommit::Type CommitType)
{
    UFrameData* currentFrame;
    TCHAR currentVal;

    if (CommitType == ETextCommit::OnEnter)                                                                                             //Check for the enter button being the trigger
    {
        bool isValidText = isTextValid(NewText);                                                                                        //Validate the entered text

        if (isValidText)        
        {

            Warning->SetVisibility(ESlateVisibility::Hidden);

            currentVal = NewText.ToString()[0];

            currentFrame = FrameList[currentFrameNum - 1];                                                                              //Get a reference to the current frame object

            currentFrame->PreviousFrame = (currentFrameNum != 1) ? FrameList[currentFrameNum - 2] : nullptr;                            //If we're on the first frame don't grab a previous frame, avoid an index fault


            if (currentVal == 'X' || currentVal == 'x')                                                                                 //Sets specific Frame data info based on if current throw is a strike
            {
                
                currentFrame->isStrike = true;
                
                subFrameScore = 10;
                currentFrameScore = 10;

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingStrikeThrows = 2;
                currentFrame->isStrike = true;

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }                                               //Sets a flag to enable 3rd throw if we're on the 10th frame

                activeStrike = true;
            }
            else if (currentVal == '/')                                                                                             //If throw is a spare set some values
            {
                currentFrame->isSpare = true;

                subFrameScore = 10 - currentFrameScore;
                currentFrameScore = 10;  

                currentFrame->FrameTotalScore = 10;
                currentFrame->FrameNum = currentFrameNum;
                currentFrame->remainingSpareThrows = 1;

                if (currentFrameNum == 10) { currentFrame->activate3rdScore = true; }                                                   //Enable 3rd throw if we're on the 10th frame

                activeSpare = true;
            }
            else
            {
                currentFrame->FrameNum = currentFrameNum;
                
                subFrameScore = currentVal - '0';                                                                                   //Used to get the int value of the currently entered number
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
            Warning->SetVisibility(ESlateVisibility::Visible);                                                                      //If text not valid, throw up warning
        }

    }
}

//Called to update the gui elements of the scoreboard and move us to the next frame
void UScoreBoardWidget::UpdateWidget()
{
    int32 newFrame;
    int32 newColumn;

    FText scoreText;

    UFrameData* CurrentFrameData;

    CurrentFrameData = FrameList[currentFrameNum - 1];

    if (currentSubFrame == 1 && !CurrentFrameData->isStrike)                                                                            //If we just had the 1st throw and isn't a strike, unlock throw 2
    {
        currentSubFrame = 2;
        newFrame = currentFrameNum;

    }
    else
    {
        if (currentFrameNum == 10)                                                                                                  
        {
            newFrame = currentFrameNum;                                                                                                 //Don't iterate past frame 10
            if (currentSubFrame == 2 && CurrentFrameData->activate3rdScore) { currentSubFrame++;}                                       //Move to 3rd throw 
        }
        else
        {
            newFrame = currentFrameNum + 1;                                                                                             //Move to first throw of next frame
            currentSubFrame = 1;
            currentFrameScore = 0;
        }

    }

    newColumn = newFrame - 1;
    CurrentFrameData = FrameList[newColumn];
    
    //Grab the text box object for the next throw
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
  
    CurrentTextBox->SetIsReadOnly(false);                                                                       //Enable input for next throw
    currentFrameNum = newFrame;
}

//Function to check previous frames for bonus points needed based on current throw
void UScoreBoardWidget::HandleStrike()
{
    UFrameData* TwoFramesBehind;
    UFrameData* LastFrame;

    if (currentFrameNum == 1)                                                                                                           //Do nothing if on first frame
    {
        return;
    }
    else if (currentFrameNum == 2)                                                                                                      //Only check back one frame if we're on frame 2
    {
        LastFrame = FrameList[currentFrameNum - 2];
        if (LastFrame->remainingStrikeThrows > 0)                                                                                       //If previous frame needs bonus additions
        {                                                                                                                               //Add the current throw to the previous frame's total
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
    {                                                                                                       //We always check two frames behind because the farthest you can go while still adding points for a prev strike is 2 frames
        TwoFramesBehind = FrameList[currentFrameNum - 3];
        LastFrame = FrameList[currentFrameNum - 2];

                                                                                                                //Check for pending strike bonus points 
        if (TwoFramesBehind->remainingStrikeThrows > 0)
        {
            TwoFramesBehind->FrameTotalScore = TwoFramesBehind->FrameTotalScore + subFrameScore;                //Add bonus points 
            TwoFramesBehind->remainingStrikeThrows--;                                                           //One less bonus point addition needed
            TwoFramesBehind->UpdateWidgets();                                                                   //Update widget
        }

        if (LastFrame->remainingStrikeThrows > 0)
        {
            LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;
            LastFrame->remainingStrikeThrows--;
            LastFrame->UpdateWidgets();   
        }

        if (TwoFramesBehind->remainingStrikeThrows == 0 && LastFrame->remainingStrikeThrows == 0)               //If last two frames are clear of strike additions, we have no active strikes
        {
            activeStrike = false;
        }
    }

}

//Function to track last frame for existing spare bonus points and add them for current throw
void UScoreBoardWidget::HandleSpare()
{
    UFrameData* LastFrame;


    if (currentFrameNum == 1)
    {
        return;
    }

    LastFrame = FrameList[currentFrameNum - 2];

    if (LastFrame->remainingSpareThrows > 0)                                                            //If last frame has pending bonus points
    {
        LastFrame->FrameTotalScore = LastFrame->FrameTotalScore + subFrameScore;                        //Add current throw to last frame total
        LastFrame->remainingSpareThrows--;                                                              //Signal spare additions are done
        LastFrame->UpdateWidgets();                                                                     //Update frame widget to reflect new scores
    }

    if (LastFrame->remainingSpareThrows == 0)                                                           //Set signal that there are no active spares
    {
        activeSpare = false;
    }

}

//Function to check if text entered is a valid bowling score (0-9, X, x, /)
bool UScoreBoardWidget::isTextValid(const FText& NewText)
{
    FString StringValue = NewText.ToString();

    if (StringValue.Len() == 1)                                                                                 //All valid entries are only 1 char
    {
        TCHAR textChar = StringValue[0];
        if (FChar::IsDigit(textChar))
        {
            int32 number = textChar - '0';                                                                      //Use ascii math to get the int value of the number entered
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

//Function called to set the scoreboard widget to visible
void UScoreBoardWidget::ShowWidget()
{
    SetVisibility(ESlateVisibility::Visible);
}

//Function called to close the widget safely and stop the game being played
void UScoreBoardWidget::CloseWidget()
{
    FWorldContext* worldContext;
    UWorld* currentWorld;
    TArray<AActor*> ScoreBoardActors;

    worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);

    currentWorld = worldContext->World();                                                                                                   //Reliable way to get the current world
    UE_LOG(LogTemp, Log, TEXT("CLOSE"))
    GEditor->RequestEndPlayMap();                                                                                                           //Stops playing the current map
    
    UGameplayStatics::GetAllActorsOfClass(currentWorld, AScoreBoardActor::StaticClass(), ScoreBoardActors);                                 //Get our custom actor that we spawns

    for (AActor* currentActor : ScoreBoardActors)
    {
        if (currentActor) { currentActor->Destroy();}                                                                                       //Delete our custom actor from the level
    }
}

//Function to reset the widget to its initial state
void UScoreBoardWidget::ResetWidget()
{
    UE_LOG(LogTemp, Log, TEXT("RESET"));

    //Iterate through each frame and set the text boxes to empty and read only
    for (UFrameData* currentData : FrameList)
    {
        
        currentData->Score1->SetText(FText::FromString(""));                    
        if (currentData->FrameNum != 1) {currentData->Score1->SetIsReadOnly(true);}                                             //First throw on first frame is only text box that is editable
        
        
        currentData->Score2->SetText(FText::FromString(""));
        currentData->Score2->SetIsReadOnly(true);

        currentData->FrameTotalScoreWidget->SetText(FText::FromString(""));

        if (currentData->Score3)
        {
            currentData->Score3->SetText(FText::FromString(""));
            currentData->Score2->SetIsReadOnly(true);
        }
    }

    //Reset to default values
    currentFrameNum = 1;
    currentFrameScore = 0;
    currentSubFrame = 1;

    activeStrike = false;
    activeSpare = false;


    remainingStrikeReps = 0;
    subFrameScore = 0;
}

//Delegate called when close button is clicked
void UScoreBoardWidget::OnCloseButtonClicked()
{
    CloseWidget();
}

//Delegate called when reset button is clicked
void UScoreBoardWidget::OnResetButtonClicked()
{
    ResetWidget();
}