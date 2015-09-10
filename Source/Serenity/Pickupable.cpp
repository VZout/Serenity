// Copyright Viktor Zoutman

#include "Serenity.h"
#include "PlayerShip.h"
#include "Pickupable.h"


// Sets default values
APickupable::APickupable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickedup = false;

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
		UE_LOG(LogTemp, Warning, TEXT("Pickupable pickuped"));
		pickedup = true;
		StaticMesh->UnregisterComponent();
	}
}
