// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActorByCurve.h"

AFloatingActorByCurve::AFloatingActorByCurve()
{

}

void AFloatingActorByCurve::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    RunningTime = 0.0f;

    Amplitude = 150.0f;
    Speed = Speed = FMath::FRandRange(3.0f, 7.0f);

    ChangeTime = 0.0f;

    // 처음 랜덤 오프셋 생성
    RandomTimeOffset = FMath::FRandRange(-0.5f, 0.5f);;

}

void AFloatingActorByCurve::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FloatCurve == nullptr)
    {
        return;
    }

    // 시간 증가
    RunningTime += DeltaTime * Speed;

    // 타이머 증가
    ChangeTime += DeltaTime;

    // 1초마다 랜덤 시간 오프셋 변경
    if (ChangeTime >= 1.0f)
    {
        ChangeTime = 0.0f;

        RandomTimeOffset = FMath::FRandRange(-0.5f, 0.5f);
    }

    // 랜덤 시간 적용
    float CurveValue = FloatCurve->GetFloatValue(RunningTime + RandomTimeOffset);

    FVector NewLocation = StartLocation;
    NewLocation.Z += CurveValue * Amplitude;

    SetActorLocation(NewLocation);
}