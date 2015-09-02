#include "Serenity.h"
#include "PlayerShip.h"
#include "Bullet.h"

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	// Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 50.0f));
	OurCamera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));

	//Rotator
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 0, 0);

	//Particle System Cruiser
	supercruisePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SuperCruiserParticleSystem"));
	supercruisePS->SetWorldLocationAndRotation(FVector(800, 0, 0), FRotator(0, 180, 0));
	supercruisePS->bAutoActivate = false;

	//Particle System Cruiser
	hyperspacePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HyperSpaceParticleSystem"));
	hyperspacePS->SetWorldLocationAndRotation(FVector(800, 0, 0), FRotator(0, 180, 0));
	hyperspacePS->bAutoActivate = false;

	firstPersonCameraPosition = FVector(0,0,0);

	AngularDamping = 1;
	camTransitionSpeed = 1;

}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	RotatingMovement->RotationRate = FRotator(CurrentAngularVelocity.Pitch * DeltaTime, CurrentAngularVelocity.Yaw * DeltaTime, CurrentAngularVelocity.Roll * DeltaTime);
	
	CurrentAngularVelocity = ZeroOutRotator(CurrentAngularVelocity, 0, AngularDamping);

	if (isFirstPerson)
		OurCamera->SetRelativeLocation(firstPersonCameraPosition);
	else
		OurCamera->SetRelativeLocation(thirdPersonCameraPosition);
}

void APlayerShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Fire0", IE_Pressed, this, &APlayerShip::Fire0);
	InputComponent->BindAction("ToggleView", IE_Pressed, this, &APlayerShip::ToggleView);
	InputComponent->BindAction("SuperCruise", IE_Pressed, this, &APlayerShip::EnableSuperCruise);
	InputComponent->BindAction("SuperCruise", IE_Released, this, &APlayerShip::DisableSuperCruise);
	InputComponent->BindAction("HyperSpace", IE_Released, this, &APlayerShip::ToggleHyperSpace);

	InputComponent->BindAxis("MoveX", this, &APlayerShip::Move_XAxis);
	InputComponent->BindAxis("Yaw", this, &APlayerShip::Yaw);
	InputComponent->BindAxis("Pitch", this, &APlayerShip::Pitch);
	InputComponent->BindAxis("Roll", this, &APlayerShip::Roll);

}

void APlayerShip::Move_XAxis(float axisValue)
{
	// Move at ... units per second forward or backward
	//CurrentVelocity.X += FMath::Clamp(axisValue, -1.0f, 1.0f) * 5.0f;
	AddMovementInput(GetActorForwardVector(), axisValue * 5.0f);
}

void APlayerShip::Yaw(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentAngularVelocity.Yaw += FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerShip::Pitch(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentAngularVelocity.Pitch += FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerShip::Roll(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentAngularVelocity.Roll += FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerShip::EnableSuperCruise() {
	supercruisePS->ActivateSystem(true);
}

void APlayerShip::DisableSuperCruise() {
	supercruisePS->DeactivateSystem();
}

void APlayerShip::ToggleHyperSpace() {
	enteringHyperspace = !enteringHyperspace;

	if (enteringHyperspace) {
		hyperspacePS->ActivateSystem(true);
		GetWorldTimerManager().SetTimer(this, &APlayerShip::EnterHyperSpace, 4.f, false);
	}
	else {
		hyperspacePS->DeactivateSystem();
		GetWorldTimerManager().ClearTimer(this, &APlayerShip::EnterHyperSpace);
	}
}

void APlayerShip::EnterHyperSpace() {
	UGameplayStatics::OpenLevel(this, TEXT("HyperSpace"));
	GetWorldTimerManager().ClearTimer(this, &APlayerShip::EnterHyperSpace);
}

void APlayerShip::Fire0() {
	TArray<FName> sockets = OurVisibleComponent->GetAllSocketNames();
	for (size_t i = 0; i < sockets.Num(); i++) {
		if (sockets[i].ToString().Contains("Weapon0")) {
			const FVector  Socket0Loc = OurVisibleComponent->GetSocketLocation(sockets[i]);
			const FRotator Socket0Rot = OurVisibleComponent->GetSocketRotation(sockets[i]);
			APlayerShip::SpawnBP<ABullet>(GetWorld(), bullet, Socket0Loc, Socket0Rot);
		}
	}
}

FRotator APlayerShip::ZeroOutRotator(FRotator Vector, float Target, float AngularDamping) {
	if (Vector.Pitch > 0)
		Vector.Pitch -= AngularDamping;
	else if (Vector.Pitch < 0)
		Vector.Pitch += AngularDamping;

	if (Vector.Yaw > 0)
		Vector.Yaw -= AngularDamping;
	else if (Vector.Yaw < 0)
		Vector.Yaw += AngularDamping;

	if (Vector.Roll > 0)
		Vector.Roll -= AngularDamping;
	else if (Vector.Roll < 0)
		Vector.Roll += AngularDamping;

	return Vector;
}

void APlayerShip::ToggleView() {
	isFirstPerson = !isFirstPerson;
}