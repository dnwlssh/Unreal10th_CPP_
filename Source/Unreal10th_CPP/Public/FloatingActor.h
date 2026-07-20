// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class UNREAL10TH_CPP_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> AFloatingActorMesh = nullptr;

protected:

	// 시작 위치
	FVector StartLocation;

	// 누적 시간
	float RunningTime;

	// 이동 높이
	UPROPERTY(EditAnywhere, Category = "Floating")
	float Amplitude;

	// 속도
	UPROPERTY(EditAnywhere, Category = "Floating")
	float Speed;

};
