// Copyright SyntaxSultan


#include "Characters/EFDCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/EFDAbilitySystemComponent.h"

AEFDCharacterBase::AEFDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AEFDCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEFDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AEFDCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AEFDCharacterBase::InitAbilityActorInfo()
{
	
}

void AEFDCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffect);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AEFDCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AEFDCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	UEFDAbilitySystemComponent* EFDASC = CastChecked<UEFDAbilitySystemComponent>(AbilitySystemComponent);
	EFDASC->AddCharacterAbilities(StartupAbilities);
}
