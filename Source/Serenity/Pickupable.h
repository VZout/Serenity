// Copyright Viktor Zoutman

#pragma once

#include "GameFramework/Actor.h"
#include "Pickupable.generated.h"

UCLASS()
class SERENITY_API APickupable : public AActor
{
	GENERATED_BODY()
	
public:	
	bool pickedup;

	// Sets default values for this actor's properties
	APickupable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnOverlap( class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
};
