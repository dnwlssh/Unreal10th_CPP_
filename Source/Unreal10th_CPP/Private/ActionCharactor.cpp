#include "ActionCharactor.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

AActionCharactor::AActionCharactor()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    CameraSpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
    CameraComponent->SetupAttachment(CameraSpringArmComponent);

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    CameraSpringArmComponent->bUsePawnControlRotation = true;

}

void AActionCharactor::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AActionCharactor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;

    UE_LOG(LogTemp, Warning, TEXT("Current Speed : %.2f"), CurrentSpeed);

}

void AActionCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent =
        Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(
            IA_Test,
            ETriggerEvent::Started,
            this,
            &AActionCharactor::OnTestAction);

        EnhancedInputComponent->BindAction(
            IA_Move,
            ETriggerEvent::Triggered,
            this,
            &AActionCharactor::OnMove);

        EnhancedInputComponent->BindAction(
            IA_Run,
            ETriggerEvent::Started,
            this,
            &AActionCharactor::RunStart);

        EnhancedInputComponent->BindAction(
            IA_Run,
            ETriggerEvent::Completed,
            this,
            &AActionCharactor::RunEnd);
    }
}

void AActionCharactor::OnTestAction(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("TestAction 실행"));
}

void AActionCharactor::OnMove(const FInputActionValue& Value)
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

void AActionCharactor::RunStart(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
  
}

void AActionCharactor::RunEnd(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
   
}