// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorLever.generated.h"

UCLASS()
class TESTRINGTAILSTUDIOS_API ADoorLever : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorLever();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UBoxComponent* TriggerBox; //Overlap volume. This is for triggering events 

	/*
	This (TriggerBox) trigger have two mesh: one for the trigger button; 
	one for the door,
	that rises when button is pressed  
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
		class UStaticMeshComponent* FloorSwitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
		class UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitailDoorLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitialSwitchLocation;

	FTimerHandle SwitchHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
		float SwitchTime;

	bool bCharacterOnSwitch;

	void CloseDoor();


protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	// all param for OnOverlapBegin from PrimitiveComponent.h

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateDoorLocation(float ZDoorLocation);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateSwitchLocation(float ZSwitchLocation);
	
	/*
		BlueprintImplementableEvent
	*/

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void RaiseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void LowerFloorSwitch();
};
