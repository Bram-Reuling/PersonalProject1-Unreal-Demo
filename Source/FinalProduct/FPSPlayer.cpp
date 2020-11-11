// Project made by Bram Reuling (2020)


#include "FPSPlayer.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a component that can be attached to another component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	// Checks if the component is not a null pointer
	check(FPSCameraComponent != nullptr);

	// Attaches the FPSCameraComponent to the CapsuleComponent of the Character
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	// FPS MESH
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Can the owner see the mesh?
	FPSMesh->SetOnlyOwnerSee(true);

	// Attaches the FPSMesh to the FPSCameraComponent
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// The mesh does not cast any dynamic shadows
	FPSMesh->bCastDynamicShadow = false;
	// The mesh does not cast any dynamic shadows
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binds the actions and axis declared in the settings of the project
	// with the functions created in this class.
	// For example: keys W & S calls MoveForward
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSPlayer::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSPlayer::StopJump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSPlayer::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPSPlayer::StopCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSPlayer::Fire);
}

void AFPSPlayer::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSPlayer::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AFPSPlayer::StartJump()
{
	bPressedJump = true;
}

void AFPSPlayer::StopJump()
{
	bPressedJump = false;
}

void AFPSPlayer::StartCrouch()
{
	Crouch();
}

void AFPSPlayer::StopCrouch()
{
	UnCrouch();
}

void AFPSPlayer::Fire()
{
	if (ProjectileClass)
	{
		// Gets the camera location and rotation
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 2.5f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawns a projectile of ProjectileClass at the specified location and with the specified rotation
			// and with the spawnparams.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
