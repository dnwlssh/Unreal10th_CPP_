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

// Called every frame