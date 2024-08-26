// Copyright SyntaxSultan


#include "Player/EFDPlayerState.h"

#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "Net/UnrealNetwork.h"

AEFDPlayerState::AEFDPlayerState()
{
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UEFDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UEFDAttributeSet>("AttributeSet");
}

void AEFDPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEFDPlayerState, Level);
}

UAbilitySystemComponent* AEFDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEFDPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
