// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "FrameData.h"
#include "ScoreBoardWidget.generated.h"

/*
    Main Widget class for our ScoreBoard Widget as a whole

    Contains all the neccessary functions and properties for managing GUI elements and implementing the scoreboard features

*/

UCLASS()
class BOWLINGSCOREBOARD_API UScoreBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    //Constructors
    UScoreBoardWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    //GUI management and Data tracking
    void HandleStrike();
    void HandleSpare();
    void HandleTextBox(UEditableTextBox* currentTextBox, int32 currentColumn, int32 currentRow);
    void ParseChildren(UPanelWidget* TopWidget, int32 column = 0, int32 row = 0);
    void SetupWidget();

    //Widget Functionality
    void ShowWidget();
    void UpdateWidget();
    void CloseWidget();
    void ResetWidget();

    //Data tracking variables
    bool activeStrike;
    bool activeSpare;

    int32 currentFrameNum;
    int32 currentSubFrame;
    int32 currentFrameScore;
    int32 remainingStrikeReps;
    int32 subFrameScore;

    UEditableTextBox* CurrentTextBox;


    //Utility Functions
    bool isTextValid(const FText& NewText);


    //Event handling functions
    UFUNCTION()
    void OnTextChanged(const FText& NewText, ETextCommit::Type CommitType);

    UFUNCTION()
    void OnCloseButtonClicked();

    UFUNCTION()
    void OnResetButtonClicked();



    //Properties connected to the WidgetBlueprint
    UPROPERTY(meta = (BindWidget))
    UGridPanel* GridPanel;
    
    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;

    UPROPERTY(meta= (BindWidget))
    UTextBlock* Warning;

    //Main list of all Frame Objects
    TArray<UFrameData*> FrameList;

};
