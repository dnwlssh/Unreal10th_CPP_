// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloatingActor.h"
#include "Curves/CurveFloat.h"
#include "FloatingActorByCurve.generated.h"


UCLASS()
class UNREAL10TH_CPP_API AFloatingActorByCurve : public AFloatingActor
{
	GENERATED_BODY()

public:
    AFloatingActorByCurve();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere)
    UCurveFloat* FloatCurve = nullptr;

    // 랜덤 시간 오프셋
    float RandomTimeOffset = 0.0f;

    // 오프셋 변경용 타이머
    float ChangeTime = 0.0f;

};
