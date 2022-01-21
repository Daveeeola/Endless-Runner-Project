// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LivesCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWIdget))
	class UButton* PauseBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPauseClick();

	public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AEndlessRunnerGameModeBase* RunnerGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinSCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void SetLivesCount(int32 Count);

	
	
	
};
