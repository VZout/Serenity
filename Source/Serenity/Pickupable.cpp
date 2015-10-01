// Copyright Viktor Zoutman

#include "Serenity.h"
#include "PlayerShip.h"
#include "Pickupable.h"
#include "SerenityGameMode.h"


// Sets default values
APickupable::APickupable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickedup = false;
	cargoType = 0;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickupable::OnOverlap);

}

// Called when the game starts or when spawned
void APickupable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickupable::OnOverlap( class AActor* OtherActor, 
							class UPrimitiveComponent* OtherComp,
						    int32 OtherBodyIndex,
							bool bFromSweep, 
							const FHitResult & SweepResult) {

	if(OtherActor->IsA(APlayerShip::StaticClass()) && !pickedup) {
		pickedup = true;
		StaticMesh->UnregisterComponent();

		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

		if(gm) {
			gm->AddMoney(moneyReward);

			if (gm->HasActiveQuestByType(98) && cargoType == 0) {
				gm->AddProgressToQuest(1, gm->GetActiveQuestByType(98).id);
			}	
			if (cargoType != 0) {
				gm->AddCargo(cargoType);
			}
		}

	}
}
