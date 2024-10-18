// Copyright SyntaxSultan


#include "Player/EFDPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EFDGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/EFDInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widgets/DamageTextComponent.h"

AEFDPlayerController::AEFDPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AEFDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext); 

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AEFDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEFDInputComponent* EFDInputComponent = CastChecked<UEFDInputComponent>(InputComponent);
	
	EFDInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEFDPlayerController::Move);
	EFDInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AEFDPlayerController::ShiftPressed);
	EFDInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AEFDPlayerController::ShiftReleased);
	EFDInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AEFDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AEFDPlayerController::ShowDamageNumber_Implementation(float DamageAmount, AActor* TargetActor, bool bBlock, bool bCritical)
{
	if (IsValid(TargetActor) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetActor, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlock, bCritical);
	}	
}

void AEFDPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AEFDPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FEFDGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AEFDPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FEFDGameplayTags::Get().InputTag_LMB))
	{
		if (GetEFDAbilitySystemComponent())
		{
			GetEFDAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	
	if (GetEFDAbilitySystemComponent()) GetEFDAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	
	if (!bTargeting && !bShiftDown)
	{
		if (const APawn* ControlledPawn = GetPawn(); FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AEFDPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FEFDGameplayTags::Get().InputTag_LMB))
	{
		if (GetEFDAbilitySystemComponent())
		{
			GetEFDAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting || bShiftDown)
	{
		if (GetEFDAbilitySystemComponent())
		{
			GetEFDAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

void AEFDPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputActionVector = Value.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputActionVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputActionVector.X);
	}
}

void AEFDPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

UEFDAbilitySystemComponent* AEFDPlayerController::GetEFDAbilitySystemComponent()
{
	if (EFDAbilitySystem == nullptr)
	{
		EFDAbilitySystem = Cast<UEFDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return EFDAbilitySystem;
}


