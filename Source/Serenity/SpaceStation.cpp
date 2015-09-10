// Copyright Viktor Zoutman

#include "Serenity.h"
#include "PlayerShip.h"
#include "SerenityGameMode.h"
#include "SpaceStation.h"


// Sets default values
ASpaceStation::ASpaceStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASpaceStation::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASpaceStation::OnLeaveOverlap);
}

// Called when the game starts or when spawned
void ASpaceStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceStation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ASpaceStation::OnOverlap( class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp,
						    int32 OtherBodyIndex,
							bool bFromSweep, 
							const FHitResult & SweepResult) {

	if(OtherActor->IsA(APlayerShip::StaticClass())) {
		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

		if(gm) {
			APlayerController* MyController = GetWorld()->GetFirstPlayerController();
			MyController->bShowMouseCursor = true;
			MyController->bEnableClickEvents = true;
			MyController->bEnableMouseOverEvents = true;

			gm->ChangeMenuWidget(questWidget);
				
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Could not get Current Game Mode"));
		}
	}
}

void ASpaceStation::OnLeaveOverlap( class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp,
						    int32 OtherBodyIndex) {

	if(OtherActor->IsA(APlayerShip::StaticClass())) {
		ExitSpaceStation();
	}
}

void ASpaceStation::ExitSpaceStation() {
		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

		if(gm) {
			APlayerController* MyController = GetWorld()->GetFirstPlayerController();
			MyController->bShowMouseCursor = false;
			MyController->bEnableClickEvents = false;
			MyController->bEnableMouseOverEvents = false;
			gm->ChangeMenuWidget(gm->StartingWidgetClass);
				
		} else {
			UE_LOG(LogTemp, Warning, TEXT("(Exit) Could not get Current Game Mode"));
		}
}
