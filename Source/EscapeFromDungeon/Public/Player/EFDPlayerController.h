// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "EFDPlayerController.generated.h"

class USplineComponent;
class UEFDAbilitySystemComponent;
struct FInputActionValue;
class UEFDInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEFDPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed()  { bShiftDown = true;  };
	void ShiftReleased() { bShiftDown = false; };
	bool bShiftDown = false;
	
	void Move(const FInputActionValue& Value);
	
	void CursorTrace();
	FHitResult CursorHit;
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UEFDInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UEFDAbilitySystemComponent> EFDAbilitySystem;

	UEFDAbilitySystemComponent* GetEFDAbilitySystemComponent();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.75f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
	void AutoRun();
};
