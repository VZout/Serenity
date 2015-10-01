// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet() {
	PrimaryActorTick.bCanEverTick = true;

	speed = 200;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//OurVisibleComponent->AttachTo(RootComponent);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	Sphere->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

void ABullet::BeginPlay() {
	Super::BeginPlay();	
}

void ABullet::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
	Sphere->SetNotifyRigidBodyCollision(true);
	ProjectileMovement->Velocity = temp + (GetActorForwardVector() * speed);
}

void ABullet::SetVelocity(FVector vel) {
	temp = vel;
}

void ABullet::OnHit(class AActor* OtherActor,
class UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& hit
	) {

	UE_LOG(LogTemp, Warning, TEXT("Hitdetecteddetecteddcetected"));

}
