#include "Serenity.h"
#include "PlayerShip.h"
#include "Bullet.h"
#include "SerenityGameMode.h"

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	//SetActorEnableCollision(true);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Create camera spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-10.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 20.0f;
	
	// Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 50.0f));
	OurCamera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));

	//Rotator
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 0, 0);

	floatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Particle System Cruiser
	supercruisePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SuperCruiserParticleSystem"));
	supercruisePS->SetWorldLocationAndRotation(FVector(800, 0, 0), FRotator(0, 180, 0));
	supercruisePS->bAutoActivate = false;

	//Particle System Cruiser
	hyperspacePS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HyperSpaceParticleSystem"));
	hyperspacePS->SetWorldLocationAndRotation(FVector(800, 0, 0), FRotator(0, 180, 0));
	hyperspacePS->bAutoActivate = false;

	firstPersonCameraDistance = 0;
	thirdPersonCameraDistance = 150;

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

	if (isFirstPerson) {
		//OurCamera->SetRelativeLocation(firstPersonCameraPosition);
		SpringArm->RelativeRotation = firstPersonCameraRotation;
		SpringArm->TargetArmLength = firstPersonCameraDistance;
		SpringArm->bEnableCameraLag = false;
	}
	else {
		//OurCamera->SetRelativeLocation(thirdPersonCameraPosition);
		SpringArm->RelativeRotation = thirdPersonCameraRotation;
		SpringArm->TargetArmLength = thirdPersonCameraDistance;
		SpringArm->bEnableCameraLag = true;
	}

	if (enteringHyperspace) {
		if (!RotatingMovement->RotationRate.IsNearlyZero(20)) {
			ToggleHyperSpace();
		}
	}
}

void APlayerShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Fire0", IE_Pressed, this, &APlayerShip::Fire0);
	InputComponent->BindAction("ToggleView", IE_Pressed, this, &APlayerShip::ToggleView);
	InputComponent->BindAction("SuperCruise", IE_Pressed, this, &APlayerShip::EnableSuperCruise);
	InputComponent->BindAction("SuperCruise", IE_Released, this, &APlayerShip::DisableSuperCruise);
	InputComponent->BindAction("HyperSpace", IE_Released, this, &APlayerShip::ToggleHyperSpace);
	InputComponent->BindAction("ToggleInventory", IE_Released, this, &APlayerShip::ToggleInventory);
	InputComponent->BindAction("ToggleJournal", IE_Released, this, &APlayerShip::ToggleQuestLog);

	InputComponent->BindAxis("MoveX", this, &APlayerShip::Move_XAxis);
	InputComponent->BindAxis("Yaw", this, &APlayerShip::Yaw);
	InputComponent->BindAxis("Pitch", this, &APlayerShip::Pitch);
	InputComponent->BindAxis("Roll", this, &APlayerShip::Roll);

}

void APlayerShip::Move_XAxis(float axisValue)
{
	AddMovementInput(GetActorForwardVector(), axisValue * 5.0f);
}

void APlayerShip::Yaw(float AxisValue)
{
		CurrentAngularVelocity.Yaw += FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void APlayerShip::Pitch(float AxisValue)
{
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
		//GetWorldTimerManager().SetTimer(this, &APlayerShip::EnterHyperSpace, 4.f, false);
		GetWorldTimerManager().SetTimer(hyperspaceTimeHandler, this, &APlayerShip::EnterHyperSpace, 4.f, false);
	}
	else {
		hyperspacePS->DeactivateSystem();
		//GetWorldTimerManager().ClearTimer(this, &APlayerShip::EnterHyperSpace);
		GetWorldTimerManager().ClearTimer(hyperspaceTimeHandler);
	}
}

void APlayerShip::EnterHyperSpace() {
	UGameplayStatics::OpenLevel(this, TEXT("HyperSpace"));
	//GetWorldTimerManager().ClearTimer(this, &APlayerShip::EnterHyperSpace);
	GetWorldTimerManager().ClearTimer(hyperspaceTimeHandler);
}

void APlayerShip::Fire0() {
	TArray<FName> sockets = OurVisibleComponent->GetAllSocketNames();
	for (size_t i = 0; i < sockets.Num(); i++) {
		if (sockets[i].ToString().Contains("Weapon0")) {
			const FVector Socket0Loc = OurVisibleComponent->GetSocketLocation(sockets[i]);
			const FRotator Socket0Rot = OurVisibleComponent->GetSocketRotation(sockets[i]);
			ABullet* bul = APlayerShip::SpawnBP<ABullet>(GetWorld(), bullet, Socket0Loc, Socket0Rot);
			bul->SetVelocity(floatingMovement->Velocity);
			UE_LOG(LogTemp, Warning, TEXT("CFireee"));
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

void APlayerShip::OpenInventory() {
	inventoryIsOpen = true;
	questlogIsOpen = false;
	ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

	if(gm) {
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
		gm->ChangeMenuWidget(inventoryWidget);
				
	} else {
		UE_LOG(LogTemp, Warning, TEXT("(Inv Enter) Could not get Current Game Mode"));
	}
}

void APlayerShip::ToggleInventory() {
	if(inventoryIsOpen) {
		CloseInventory();
	} else {
		OpenInventory();
	}
}

void APlayerShip::CloseInventory() {
	inventoryIsOpen = false;
		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

	if(gm) {
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		MyController->bShowMouseCursor = false;
		MyController->bEnableClickEvents = false;
		MyController->bEnableMouseOverEvents = false;
		gm->ChangeMenuWidget(gm->StartingWidgetClass);
				
	} else {
		UE_LOG(LogTemp, Warning, TEXT("(Inv Exit) Could not get Current Game Mode"));
	}
}

void APlayerShip::OpenQuestLog() {
	inventoryIsOpen = false;
	questlogIsOpen = true;
	ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

	if(gm) {
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
		gm->ChangeMenuWidget(questlogWidget);
				
	} else {
		UE_LOG(LogTemp, Warning, TEXT("(Inv Enter) Could not get Current Game Mode"));
	}
}

void APlayerShip::ToggleQuestLog() {
	if(questlogIsOpen) {
		CloseQuestLog();
	} else {
		OpenQuestLog();
	}
}

void APlayerShip::CloseQuestLog() {
	questlogIsOpen = false;
		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

	if(gm) {
		APlayerController* MyController = GetWorld()->GetFirstPlayerController();
		MyController->bShowMouseCursor = false;
		MyController->bEnableClickEvents = false;
		MyController->bEnableMouseOverEvents = false;
		gm->ChangeMenuWidget(gm->StartingWidgetClass);
				
	} else {
		UE_LOG(LogTemp, Warning, TEXT("(Inv Exit) Could not get Current Game Mode"));
	}
}
