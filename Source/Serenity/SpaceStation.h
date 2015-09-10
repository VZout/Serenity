// Copyright Viktor Zoutman

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "SpaceStation.generated.h"

UCLASS()
class SERENITY_API ASpaceStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceStation();

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

	UFUNCTION()
	void OnLeaveOverlap( class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ExitSpaceStation();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> questWidget;
	
};
