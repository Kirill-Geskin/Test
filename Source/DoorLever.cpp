// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorLever.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ADoorLever::ADoorLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	SwitchTime = 2.f;
	bCharacterOnSwitch = false;
}

void ADoorLever::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorLever::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoorLever::OnOverlapEnd);

	InitailDoorLocation = Door->GetComponentLocation();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
}

// Called every frame
void ADoorLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorLever::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	if (!bCharacterOnSwitch)
	{
		bCharacterOnSwitch = true;
	}
	RaiseDoor();
	LowerFloorSwitch();
}

void ADoorLever::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
	if (bCharacterOnSwitch)
	{
		bCharacterOnSwitch = false;
	}
	GetWorldTimerManager().SetTimer(SwitchHandle, this, &ADoorLever::CloseDoor, SwitchTime);
}

void ADoorLever::UpdateDoorLocation(float ZDoorLocation)
{
	FVector NewLocation = InitailDoorLocation;
	NewLocation.Z += ZDoorLocation;
	Door->SetWorldLocation(NewLocation);
}

void ADoorLever::UpdateSwitchLocation(float ZSwitchLocation)
{
	FVector NewLocation = InitialSwitchLocation;
	NewLocation.Z += ZSwitchLocation;
	FloorSwitch->SetWorldLocation(NewLocation);
}

void ADoorLever::CloseDoor()
{
	if (!bCharacterOnSwitch)
	{
		LowerDoor();
		RaiseFloorSwitch();
	}
}
