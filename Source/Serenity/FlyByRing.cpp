// Copyright Viktor Zoutman

#include "Serenity.h"
#include "PlayerShip.h"
#include "SerenityGameMode.h"
#include "FlyByRing.h"

AFlyByRing::AFlyByRing()
{
	PrimaryActorTick.bCanEverTick = true;

	isTarget;
	flyThroughs = 0;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	Box->AttachTo(RootComponent);
	Box->OnComponentBeginOverlap.AddDynamic(this, &AFlyByRing::OnOverlap);

}

void AFlyByRing::BeginPlay() {
	OnSpawned();
}

void AFlyByRing::OnSpawned() {
	if (isTarget) {
		StaticMesh->SetMaterial(1, targetMaterial);
	}
	else {
		StaticMesh->SetMaterial(1, activeMaterial);
	}
}

void AFlyByRing::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AFlyByRing::OnOverlap(class AActor* OtherActor,
class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult) {

	if (OtherActor->IsA(APlayerShip::StaticClass()) && isTarget) {

		ASerenityGameMode* gm = (ASerenityGameMode*)GetWorld()->GetAuthGameMode();

		if (gm) {
			if (gm->HasActiveQuestByType(97) && flyThroughs < 1) {
				gm->AddProgressToQuest(1, gm->GetActiveQuestByType(97).id);
				SetActive(false);
				if (!isFinal) {
					SetNextActive();
				}
			flyThroughs++;
			}
		}
	}
}

int32 AFlyByRing::GetID() {
	return id;
}

int32 AFlyByRing::GetFlyThroughs() {
	return flyThroughs;
}

void AFlyByRing::SetActive(bool value) {
	if (value) {
		StaticMesh->SetMaterial(1, activeMaterial);
	} else {
		StaticMesh->SetMaterial(1, inactiveMaterial);
	}
}	

void AFlyByRing::SetTarget() {
	StaticMesh->SetMaterial(1, targetMaterial);
	isTarget = true;
}

void AFlyByRing::SetNextActive() {
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		if (ActorItr->IsA(AFlyByRing::StaticClass())) {
			AFlyByRing* fbr = (AFlyByRing*)*ActorItr;
			if (fbr->id == (id + 1)) {
				fbr->SetTarget();
			}
		}
	}
}

void AFlyByRing::ResetChilds() {
	StaticMesh->SetWorldLocationAndRotation(GetActorLocation(), GetActorRotation());
	Box->SetRelativeLocationAndRotation(GetActorLocation(), GetActorRotation());
}