// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	if(MainMenuScreenClass)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(),MainMenuScreenClass);

		if(Widget)
		{
			Widget->AddToViewport();
		}
	}
}
