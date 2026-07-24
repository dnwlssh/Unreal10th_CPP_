#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ActionCharactor.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREAL10TH_CPP_API AActionCharactor : public ACharacter
{
    GENERATED_BODY()

public:
    AActionCharactor();

protected:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

    void OnTestAction(const FInputActionValue& Value);

    void OnMove(const FInputActionValue& Value);

    void RunStart(const FInputActionValue& Value);

    void RunEnd(const FInputActionValue& Value);

    void OnRoll(const FInputActionValue& Value);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> IA_Test;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> IA_Move;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> IA_Run;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> IA_Roll;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TWeakObjectPtr<UAnimMontage> RollMontage;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USpringArmComponent> CameraSpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UCameraComponent> CameraComponent = nullptr;

protected:

    UPROPERTY(EditAnywhere, Category = "Move")
    float WalkSpeed = 600.f;

    UPROPERTY(EditAnywhere, Category = "Move")
    float RunSpeed = 1200.f;

private:
    UPROPERTY()
    TObjectPtr<UAnimInstance> AnimInstance = nullptr;

    bool bSprintMode = false;

};