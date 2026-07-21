// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ActionPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
//Class UInput
/**
 * 
 */
UCLASS()
class UNREAL10TH_CPP_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappinContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Look = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Move = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> IA_Run = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ViewPitchMax = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ViewPitchMin = -40;

private:
	void OnLookInput(const FInputActionValue& InValue);
	
private:
	// 입력 우선 순위
	int32 GameInputPriority = 1;
};
