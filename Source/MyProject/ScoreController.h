// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreController.generated.h"

UCLASS()
class MYPROJECT_API AScoreController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreController();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Widgets")
	TSubclassOf<class UUserWidget> ScoreTextWidget;
	TWeakObjectPtr<class UUserWidget> pScoreTextWidget;
	TWeakObjectPtr<class UTextBlock> pScoreText;
	TWeakObjectPtr<class UTextBlock> pBulletText;
	TWeakObjectPtr<class UTextBlock> pPullsText;
	TWeakObjectPtr<class UTextBlock> pTimerText;
	TWeakObjectPtr<class UTextBlock> pGameOverText;

	UFUNCTION(BlueprintCallable, Category= "Score")
	void IncreaseScore(int amount);

	UFUNCTION(BlueprintCallable, Category= "Score")
	void DecreaseBullets();

	UFUNCTION(BlueprintCallable, Category= "Score")
	void ResetBullets();

	UFUNCTION(BlueprintCallable, Category= "Score")
	int GetScore() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int Score;
	int Bullets;
	int Pulls;
	float Timer;
};
