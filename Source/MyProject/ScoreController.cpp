// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreController.h"

#include <iso646.h>

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

// Sets default values
AScoreController::AScoreController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreController::BeginPlay()
{
	Super::BeginPlay();

	if(ScoreTextWidget)
	{
		pScoreTextWidget = CreateWidget<UUserWidget>(GetGameInstance(), ScoreTextWidget);

		if(pScoreTextWidget.IsValid())
		{
			pScoreTextWidget->AddToViewport();
			pScoreText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("ScoreText");
			pBulletText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("Bullets");
			pPullsText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("PullsText");
			pTimerText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("Timer");
			pGameOverText = (UTextBlock*)pScoreTextWidget->GetWidgetFromName("GameOver");
		}
	}

	Bullets = 3;
	Pulls = 5;
	Timer = 15.0f;

	if(pBulletText.IsValid())
	{
		pBulletText->SetText(FText::FromString(FString::FromInt(Bullets)));
	}

	if(pPullsText.IsValid())
	{
		pPullsText->SetText(FText::FromString(FString::FromInt(Pulls)));
	}

	if(pPullsText.IsValid())
	{
		pTimerText->SetText(FText::FromString(FString::FromInt(Timer)));
	}
}

// Called every frame
void AScoreController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Score < 800 && Timer > 0)
	{
		Timer -= DeltaTime;
		pTimerText->SetText(FText::FromString(FString::FromInt(Timer)));
		if(Timer < 10)
		{
			pTimerText->SetText(FText::FromString("0" + FString::FromInt(Timer)));
		}
	}
	else
	{
		if(Score >= 800)
		{
			pTimerText->SetText(FText::FromString(""));
		}

		if(Timer < 0)
		{
			Timer = 0;
			pGameOverText->SetText(FText::FromString("Game Over"));
		}
	}
}

void AScoreController::IncreaseScore(int amount)
{
	if(pScoreText.IsValid())
	{
		Score += amount;
		pScoreText->SetText(FText::FromString(FString::FromInt(Score)));
	}
}

void AScoreController::DecreaseBullets()
{
	if(pBulletText.IsValid())
	{
		Bullets--;
		pBulletText->SetText(FText::FromString(FString::FromInt(Bullets)));
	}
}

void AScoreController::ResetBullets()
{
	if(pPullsText.IsValid() and pBulletText.IsValid())
	{
		Bullets = 3;
		Pulls--;
		pBulletText->SetText(FText::FromString(FString::FromInt(Bullets)));
		pPullsText->SetText(FText::FromString(FString::FromInt(Pulls)));
	}
}

int AScoreController::GetScore() const
{
	return Score;
}
