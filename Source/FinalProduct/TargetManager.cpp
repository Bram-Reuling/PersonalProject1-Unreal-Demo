// Project made by Bram Reuling (2020)


#include "TargetManager.h"

// Sets default values
ATargetManager::ATargetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnTargets();

}

// Called when the game starts or when spawned
void ATargetManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetManager::SpawnTargets()
{
	if (TargetClass)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("YEET")));
		UWorld* World = GetWorld();
		if (World)
		{
			for (ATargetPoint* T : TargetPoints)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;

				FVector Position = T->GetTransform().GetLocation();

				Position.Y += 2;

				FRotator Rotation = T->GetTransform().GetRotation().Rotator();
				
				ATarget* Target = World->SpawnActor<ATarget>(TargetClass, Position, Rotation,SpawnParameters);
			}
		}
	}
}
int ATargetManager::GetSpawnPoints()
{
	return TargetPoints.Num();
}
