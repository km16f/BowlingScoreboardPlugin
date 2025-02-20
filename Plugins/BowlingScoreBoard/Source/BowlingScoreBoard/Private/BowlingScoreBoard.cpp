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

//Called when the plugin button in the "Window" toolbar menu is clicked
void FBowlingScoreBoardModule::PluginButtonClicked()
{
	SetupActor();
	PlayScene();

}

//Function to mirror pressing play in the scene to start the widget
void FBowlingScoreBoardModule::PlayScene() 
{
	if (GEditor)
	{
		FRequestPlaySessionParams params = FRequestPlaySessionParams();
		GEditor->RequestPlaySession(params);
	}
}

//Function to spawn our custom actor and popup our scoreboard widget
void FBowlingScoreBoardModule::SetupActor()
{
	AScoreBoardActor* newActor;

	FTransform tempTransform;
	FActorSpawnParameters tempParameters;
	FWorldContext* worldContext;
	UWorld* currentWorld;

	UClass* ScriptActorClass;
	UClass* ScoreBoardWidgetClass;

	ScriptActorClass = LoadClass<AScoreBoardActor>(nullptr, TEXT("/Script/CoreUObject.Class'/Script/BowlingScoreBoard.ScoreBoardActor'"));										//Load custom Actor class

	if (ScriptActorClass)
	{
		worldContext = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);																						//Reliable way to get the current world object for spawning

		currentWorld = worldContext->World();
		if (currentWorld)
		{
			newActor = currentWorld->SpawnActor<AScoreBoardActor>(ScriptActorClass, tempTransform, tempParameters);															//Spawn our actor

			ScoreBoardWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/BowlingScoreBoard/BP_ScoreBoardWidget.BP_ScoreBoardWidget_C'"));			//Load our custom widget blueprint class

			if (ScoreBoardWidgetClass)
			{
				UUserWidget* test = CreateWidget<UUserWidget>(currentWorld, ScoreBoardWidgetClass);																		//Set the ref property in the actor to our widget blueprint
				newActor->ScoreBoardWidgetRef = test;
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