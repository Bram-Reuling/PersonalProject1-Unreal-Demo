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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATargetManager::TTimer, 1, true);
}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Spawns the targets on the target points & resets
/// some of the values.
/// Used at the start of the game and when the
/// targets are all gone.
/// </summary>
void ATargetManager::SpawnTargets()
{
	// Resets the time in seconds and the counting state.
	TimeInSeconds = 0;
	IsCounting = false;

	// Checks if there is a TargetClass.
	// TargetClass is editable in the editor.
	if (TargetClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// A for loop that loops over all the elements in the
			// TargetPoints array.
			for (ATargetPoint* T : TargetPoints)
			{
				// Create parameters for the target
				// and assign the owner of the target
				// to this class.
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.Owner = this;

				// Spawns a target of class ATarget with the transform of the target point and the
				// parameters specified above.
				ATarget* Target = World->SpawnActor<ATarget>(TargetClass, T->GetTransform(),SpawnParameters);
			}
		}
	}
}
/// <summary>
/// Returns the number of spawn points 
/// </summary>
/// <returns></returns>
int ATargetManager::GetSpawnPoints()
{
	return TargetPoints.Num();
}

/// <summary>
/// Gets the time passed after the first target
/// has been shot.
/// </summary>
/// <returns></returns>
int ATargetManager::GetTime()
{
	return TimeInSeconds;
}

/// <summary>
/// Timer function.
/// </summary>
void ATargetManager::TTimer()
{
	if (IsCounting)
	{
		++TimeInSeconds;
	}
}

void ATargetManager::StartTimer()
{
	IsCounting = true;
}

void ATargetManager::StopTimer()
{
	IsCounting = false;
}

