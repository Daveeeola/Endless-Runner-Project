// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "FloorTile.h"
#include "GameHud.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


void AEndlessRunnerGameModeBase::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;

	GameHud = CreateWidget<UGameHud>(GetWorld(),GameHUDClass);
	check(GameHud);

	GameHud->InitializeHUD(this);
	GameHud->AddToViewport();

	NumberOfLives = MaxLives;
	
	CreateInitialFloorTile();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTile()
{
	AFloorTile* Tile = AddFloorTIle(false);

	if(Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	/*for (float value : LaneSwitchValues)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lane Value: %f"),value);
	}*/

	AddFloorTIle(false);
	AddFloorTIle(false);
	
	for (int i  = 0; i <NumInitialFloorTiles;++i)
	{
		AddFloorTIle(true);
	}
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTIle(const bool bSpawnItems)
{

	UWorld* World = GetWorld();
	if(World)
	{
		AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass,NextSpawnPoint);

		if (Tile)
		{
			FloorTiles.Add(Tile);

			if(bSpawnItems)
			{
				Tile->SpawnItems();	
			}
			
			NextSpawnPoint = Tile->GetAttachTransform();
			
		}
		return Tile;
	}
	return nullptr;
	
}

void AEndlessRunnerGameModeBase::AddCoin()
{
	TotalCoin += 1;

	OnCoinsCountChanged.Broadcast(TotalCoin);
}



void AEndlessRunnerGameModeBase::PlayerDied()
{
	NumberOfLives -= 1;
	OnLivesCountChanged.Broadcast(NumberOfLives);

	if(NumberOfLives > 0)
	{
		//Iterate over all Floor Tiles and Call Destroy Floor Tile

		for(auto Tile : FloorTiles)
		{
			if(Tile)
			{
				Tile->DestroyFloorTile();
			}
		}


		//Empty our array
		FloorTiles.Empty();

		//NextSpawnPoint to Initial Value
		NextSpawnPoint = FTransform();
		

		//Create our initial floor tiles
		CreateInitialFloorTile();

		//Broadcast the level reset event
		OnLevelReset.Broadcast();
	}

	else
	{
		GameOver();
	}
}

void AEndlessRunnerGameModeBase::GameOver()
{
	if(GameOverScreenClass)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(),GameOverScreenClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
		
	}
	
}

void AEndlessRunnerGameModeBase::RemoveTile(AFloorTile* Tile)
{
	FloorTiles.Remove(Tile);
}


