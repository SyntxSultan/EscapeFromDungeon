// Copyright SyntaxSultan


#include "Player/EFDPlayerState.h"

#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "AbilitySystem/EFDAttributeSet.h"

AEFDPlayerState::AEFDPlayerState()
{
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UEFDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UEFDAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AEFDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
