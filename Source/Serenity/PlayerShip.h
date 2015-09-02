// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

UCLASS()
class SERENITY_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	APlayerShip();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Move_XAxis(float axisValue);
	void Yaw(float axisValue);
	void Pitch(float axisValue);
	void Roll(float axisValue);
	void EnableSuperCruise();
	void DisableSuperCruise();
	void ToggleHyperSpace();
	void EnterHyperSpace();
	void ToggleView();
	void Fire0();
	FRotator ZeroOutRotator(FRotator Vector, float Target, float AngularDamping);

	FVector CurrentVelocity;
	FRotator CurrentAngularVelocity;

	UPROPERTY(EditAnywhere)
	float AngularDamping;

	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	URotatingMovementComponent* RotatingMovement;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* supercruisePS;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* hyperspacePS;
	UPROPERTY(EditAnywhere)
	UClass* bullet;

	UPROPERTY(EditAnywhere)
	bool enteringHyperspace;

	UPROPERTY(EditAnywhere)
	bool isFirstPerson;
	UPROPERTY(EditAnywhere)
	FVector firstPersonCameraPosition;
	UPROPERTY(EditAnywhere)
	FVector thirdPersonCameraPosition;
	UPROPERTY(EditAnywhere)
	float camTransitionSpeed;

	template <typename VictoryObjType>
	static FORCEINLINE VictoryObjType* SpawnBP(
		UWorld* TheWorld,
		UClass* TheBP,
		const FVector& Loc,
		const FRotator& Rot,
		const bool bNoCollisionFail = true,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
		){
		if (!TheWorld) return NULL;
		if (!TheBP) return NULL;
		//~~

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoCollisionFail = bNoCollisionFail;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<VictoryObjType>(TheBP, Loc, Rot, SpawnInfo);
	}
	
};
