// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoardActor.generated.h"

UCLASS()
class BOWLINGSCOREBOARD_API AScoreBoardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreBoardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variable used to attach widget to our actor and spawn it
	UPROPERTY(EditAnywhere)
	UUserWidget* ScoreBoardWidgetRef;

};
