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

	UPROPERTY(EditAnywhere)
	int32 cargoType;

	UPROPERTY(EditAnywhere)
	int32 moneyReward;

	APickupable();

	virtual void BeginPlay() override;
	
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
