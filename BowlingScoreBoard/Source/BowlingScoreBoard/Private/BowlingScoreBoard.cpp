// Copyright Epic Games, Inc. All Rights Reserved.

#include "BowlingScoreBoard.h"
#include "BowlingScoreBoardStyle.h"
#include "BowlingScoreBoardCommands.h"
#include "Engine/World.h"
#include "Misc/MessageDialog.h"
#include "ScoreBoardActor.h"
#include "ScoreBoardWidget.h"
#include "ToolMenus.h"
#include "WidgetBlueprint.h"


static const FName BowlingScoreBoardTabName("BowlingScoreBoard");

#define LOCTEXT_NAMESPACE "FBowlingScoreBoardModule"

void FBowlingScoreBoardModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBowlingScoreBoardStyle::Initialize();
	FBowlingScoreBoardStyle::ReloadTextures();

	FBowlingScoreBoardCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBowlingScoreBoardCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FBowlingScoreBoardModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBowlingScoreBoardModule::RegisterMenus));
}

void FBowlingScoreBoardModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBowlingScoreBoardStyle::Shutdown();

	FBowlingScoreBoardCommands::Unregister();
}

void FBowlingScoreBoardModule::PluginButtonClicked()
{
	//Function run after plugin button is clicked from Window Toolbar menu
	//This function spawns the necessary actor for our widget blueprint and start the game
	SetupActor();
	PlayScene();

}

void FBowlingScoreBoardModule::PlayScene() 
{
	//Function to play the scene so the interactive widget will popup
	if (GEditor)
	{
		FRequestPlaySessionParams params = FRequestPlaySessionParams();
		GEditor->RequestPlaySession(params);
	}
}

void FBowlingScoreBoardModule::SetupActor()
{
	//Function to load and spawn custom actor of class AScoreBoardActor 
	// This actor has a special UPROPERTY we can attach our WidgetBlueprint to, to spawn the Widget

	AScoreBoardActor* newActor;

	FTransform tempTransform;
	FActorSpawnParameters tempParameters;
	FWorldContext* worldContext;
	UWorld* currentWorld;

	UClass* ScriptActorClass;
	UClass* ScoreBoardWidgetClass;

	ScriptActorClass = LoadClass<AScoreBoardActor>(nullptr, TEXT("/Script/CoreUObject.Class'/Script/BowlingScoreBoard.ScoreBoardActor'"));  // Loads the class of our custom C++ actor

	if (ScriptActorClass)
	{
		worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);								//Most reliable way of getting the world from the default unreal viewport

		currentWorld = worldContext->World();																		// Gets us the UWorld we need to spawn actors
		if (currentWorld)
		{
			newActor = currentWorld->SpawnActor<AScoreBoardActor>(ScriptActorClass, tempTransform, tempParameters);						// Spawns the actor of our custom AScoreBoardActor class

			ScoreBoardWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/BowlingScoreBoard/BP_ScoreBoardWidget.BP_ScoreBoardWidget_C'"));				//Loads our custom UWidgetBlueprint class

			if (ScoreBoardWidgetClass)
			{
				UUserWidget* test = CreateWidget<UUserWidget>(currentWorld, ScoreBoardWidgetClass);											//Creates a widget instance of our blueprint class we need to set the UPROPERTY in our actor
				newActor->ScoreBoardWidgetRef = test;																						//Sets the UPROPERTY for our actor so our widget can spawn in the scene when we play
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Cannot Load Plugin Blueprint Widget Class"));
			}
		}
	}
}

void FBowlingScoreBoardModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBowlingScoreBoardCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBowlingScoreBoardCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBowlingScoreBoardModule, BowlingScoreBoard)