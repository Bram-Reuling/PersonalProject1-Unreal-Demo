// Project made by Bram Reuling (2020)

///
/// This class is responsible for:
/// - Spawning Targets
/// - Timer
///
/// Some of the functions in this class can be
/// accessed by the Blueprint system or UE4
/// 
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Target.h"
#include "TargetManager.generated.h"

UCLASS()
class FINALPRODUCT_API ATargetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Target)
	TSubclassOf<class ATarget> TargetClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnTargets();

	UFUNCTION(BlueprintCallable)
	int GetSpawnPoints();

	UFUNCTION(BlueprintCallable)
	int GetTime();

	UFUNCTION()
	void TTimer();
	
	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintCallable)
	void StopTimer();
	
	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> TargetPoints;

	UPROPERTY(VisibleAnywhere)
	int TimeInSeconds;

	UPROPERTY(VisibleAnywhere)
	bool IsCounting;

	FTimerHandle TimerHandle;
};
