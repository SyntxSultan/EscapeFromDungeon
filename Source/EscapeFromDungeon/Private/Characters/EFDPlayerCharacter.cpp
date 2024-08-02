// Copyright SyntaxSultan


#include "Characters/EFDPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/EFDPlayerState.h"

AEFDPlayerCharacter::AEFDPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AEFDPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init ability info for server
	InitAbilityActorInfo();
}

void AEFDPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability info for client
	InitAbilityActorInfo();
}

void AEFDPlayerCharacter::InitAbilityActorInfo()
{
	AEFDPlayerState* EFDPlayerState = GetPlayerState<AEFDPlayerState>();
	check(EFDPlayerState);
	EFDPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(EFDPlayerState, this);
	AbilitySystemComponent = EFDPlayerState->GetAbilitySystemComponent();
	AttributeSet = EFDPlayerState->GetAttributeSet();
}
