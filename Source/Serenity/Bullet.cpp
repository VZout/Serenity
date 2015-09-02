// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	speed = 200;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	ProjectileMovement->Velocity = GetActorForwardVector() * speed;

}

