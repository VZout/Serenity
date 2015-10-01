// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
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
	void OpenInventory();
	void CloseInventory();
	void ToggleInventory();
	void OpenQuestLog();
	void CloseQuestLog();
	void ToggleQuestLog();
	FRotator ZeroOutRotator(FRotator Vector, float Target, float AngularDamping);

	UPROPERTY(EditAnywhere)
	float AngularDamping;
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	UPROPERTY(EditAnywhere)
	float SuperCruiseBoostAmount;
	UPROPERTY(EditAnywhere)
	float DefaultRotateSpeed;
	UPROPERTY(EditAnywhere)
	float SuperCruiseRotateSpeed;

	float CurrentRotateSpeed;
	FVector CurrentVelocity;
	FRotator CurrentAngularVelocity;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	URotatingMovementComponent* RotatingMovement;
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* floatingMovement;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* supercruisePS;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* hyperspacePS;
	UPROPERTY(EditAnywhere)
	UClass* bullet;

	UPROPERTY(EditAnywhere)
	bool enteringHyperspace;

	bool inventoryIsOpen;
	bool questlogIsOpen;

	UPROPERTY(EditAnywhere)
	bool isFirstPerson;
	UPROPERTY(EditAnywhere)
	float firstPersonCameraDistance;
	UPROPERTY(EditAnywhere)
	float thirdPersonCameraDistance;
	UPROPERTY(EditAnywhere)
	FRotator firstPersonCameraRotation;
	UPROPERTY(EditAnywhere)
	FRotator thirdPersonCameraRotation;
	UPROPERTY(EditAnywhere)
	float camTransitionSpeed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> inventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> questlogWidget;

	FTimerHandle hyperspaceTimeHandler;

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
	if(!TheWorld) return NULL;
	if(!TheBP) return NULL;
	//~~
 
	UE_LOG(LogTemp, Warning, TEXT("Spawning Object"));

	return TheWorld->SpawnActor<VictoryObjType>(TheBP, Loc ,Rot );
}
	
};
