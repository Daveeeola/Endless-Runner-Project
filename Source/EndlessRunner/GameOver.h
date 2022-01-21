// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

	protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWIdget))
	class UButton* RestartBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWIdget))
	class UButton* MainMenuBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMainMenuClick();

	UFUNCTION()
	void OnRestartClick();
};
