// Project made by Bram Reuling (2020)

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
	
	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> TargetPoints;
};
