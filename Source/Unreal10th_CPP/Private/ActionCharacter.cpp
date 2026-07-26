// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	CameraSpringArmComponent->bUsePawnControlRotation = true;	// 스프링암은 컨트롤러 입력에 맞게 회전되기

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(CameraSpringArmComponent);

	bUseControllerRotationYaw = false;	// 컨트롤러 움직일 때 폰이 같이 회전되는 것 방지
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 캐릭터 이동방향으로 바라보게 만들기
}

float AActionCharacter::GetCurrentStamina_Implementation() const
{
	return CurrentStamina;
}

bool AActionCharacter::ConsumeStamina_Implementation(float InAmount)
{
	bool bResult = false;
	if (CurrentStamina >= InAmount)
	{
		CurrentStamina -= InAmount;
		bResult = true;
	}

	UE_LOG(LogTemp, Log, TEXT("현재 Stamina : %.1f"), CurrentStamina);
	return bResult;
}

void AActionCharacter::RecoveryStamina_Implementation(float InAmount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + InAmount, 0.0f, MaxStamina);
	UE_LOG(LogTemp, Log, TEXT("현재 Stamina : %.1f"), CurrentStamina);
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}

	CurrentStamina = MaxStamina;

	//GetCurrentStamina();	// 실행했을 때 C++에 구현된 내용만 호출한다.
	//IStaminaInterface::Execute_GetCurrentStamina(this);	// 실행했을 때 블루프린트 구현으로 호출한다.
}

void AActionCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;

    //UE_LOG(LogTemp, Warning, TEXT("Current Speed : %.2f"), CurrentSpeed);

}

void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent =
        Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(
            IA_Test,
            ETriggerEvent::Started,
            this,
            &AActionCharacter::OnTestAction);

        EnhancedInputComponent->BindAction(
            IA_Move,
            ETriggerEvent::Triggered,
            this,
            &AActionCharacter::OnMove);

        EnhancedInputComponent->BindAction(
            IA_Run,
            ETriggerEvent::Started,
            this,
            &AActionCharacter::RunStart);

        EnhancedInputComponent->BindAction(
            IA_Run,
            ETriggerEvent::Completed,
            this,
            &AActionCharacter::RunEnd);

        EnhancedInputComponent->BindAction(
            IA_Roll,
            ETriggerEvent::Started,
            this, &AActionCharacter::OnRoll);
    }
}

void AActionCharacter::OnTestAction(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("TestAction 실행"));
}

void AActionCharacter::OnMove(const FInputActionValue& Value)
{
    FVector2D MoveInput = Value.Get<FVector2D>();

    FRotator ControlRotation = GetControlRotation();
    ControlRotation.Pitch = 0.f;
    ControlRotation.Roll = 0.f;

    FVector Forward = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
    FVector Right = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(Forward, MoveInput.Y);
    AddMovementInput(Right, MoveInput.X);
}

void AActionCharacter::RunStart(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

}

void AActionCharacter::RunEnd(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AActionCharacter::OnRoll(const FInputActionValue& Value)
{
    //UE_LOG(LogTemp, Log, TEXT("OnRoll"));

    if (!RollMontage.IsValid()) return;

    if (!AnimInstance)
    {
        AnimInstance = GetMesh()->GetAnimInstance();
    }

    if (AnimInstance && !AnimInstance->IsAnyMontagePlaying())
    {
        if (!GetLastMovementInputVector().IsNearlyZero())	// 이동 입력 중이면
        {
            SetActorRotation(GetLastMovementInputVector().Rotation());	// 입력방향으로 즉시 회전해서 구르기
        }

        PlayAnimMontage(RollMontage.Get());
    }
}