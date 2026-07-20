// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// UStaticMeshComponent 타입으로 디폴트 서브 오브젝트 생성
	// 에디터 창에서 보이는 이름은 "MainMesh"로 설정
	AFloatingActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floating"));
	AFloatingActorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	RunningTime = 0.0f;
	Amplitude = 50.0f;
	Speed = 5.0f;
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	FVector NewLocation = StartLocation;

	NewLocation.Z += FMath::Cos(RunningTime * Speed) * Amplitude;

	SetActorLocation(NewLocation);

}

