// Project made by Bram Reuling (2020)


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// MESH
	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("'/Game/Cube.Cube'"));
	if (Mesh.Succeeded())
	{
		TargetMesh->SetStaticMesh(Mesh.Object);
		TargetMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	TargetMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

