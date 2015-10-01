#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SERENITY_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	void SetVelocity(FVector vel);

	UFUNCTION()
		void OnHit(class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& hit
		);

	//UPROPERTY(EditAnywhere)
	//USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	UParticleSystem* explosion;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;
	UPROPERTY(EditAnywhere)
	float speed;

	UPROPERTY(EditAnywhere)
	FVector temp;
	
};
