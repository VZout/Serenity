// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	speed = 200;
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//OurVisibleComponent->AttachTo(RootComponent);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	
}

void ABullet::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
	ProjectileMovement->Velocity = temp + (GetActorForwardVector() * speed);
}

void ABullet::SetVelocity(FVector vel) {
	temp = vel;
	UE_LOG(LogTemp, Warning, TEXT("Setting velocity"));

}

