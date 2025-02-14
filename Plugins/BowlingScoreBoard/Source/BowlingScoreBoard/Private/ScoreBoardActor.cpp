// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardActor.h"

// Sets default values
AScoreBoardActor::AScoreBoardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreBoardActor::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreBoardWidgetRef)
	{
		ScoreBoardWidgetRef->AddToViewport(0);
	}
	
}

// Called every frame
void AScoreBoardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

