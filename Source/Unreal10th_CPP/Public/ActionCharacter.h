#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../Interface/StaminaInterface.h"
#include "ActionCharacter.generated.h"

class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREAL10TH_CPP_API AActionCharacter : public ACharacter, public IStaminaInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionCharacter();

	virtual float GetCurrentStamina_Implementation() const override;
	virtual bool ConsumeStamina_Implementation(float InAmount) override;
	virtual void RecoveryStamina_Implementation(float InAmount) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 100.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> CameraSpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance = nullptr;
};