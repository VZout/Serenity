// Copyright Viktor Zoutman

#pragma once

#include "GameFramework/Actor.h"
#include "FlyByRing.generated.h"

UCLASS()
class SERENITY_API AFlyByRing : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlyByRing();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	bool isTarget;
	UPROPERTY(EditAnywhere)
	bool isFinal;
	UPROPERTY(EditAnywhere)
	int32 id;

	void SetActive(bool value);
	void SetNextActive();
	void SetTarget();
	int32 GetID();
	int32 GetFlyThroughs();
	void ResetChilds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	UMaterial* targetMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	UMaterial* activeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	UMaterial* inactiveMaterial;

	UFUNCTION()
	void OnOverlap(class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	void OnSpawned();

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

private:
	int32 flyThroughs;

	
	
};
