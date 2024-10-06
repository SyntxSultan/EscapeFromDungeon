// Copyright SyntaxSultan


#include "Characters/EFDCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "EscapeFromDungeon/EscapeFromDungeon.h"

AEFDCharacterBase::AEFDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEFDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEFDCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void AEFDCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
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

void AEFDCharacterBase::Dissolve()
{
	if (IsValid(CharDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInstance = UMaterialInstanceDynamic::Create(CharDissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInstance);
		StartCharDissolveTimeLine(DynamicMatInstance);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInstance = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInstance);
		StartWeaponDissolveTimeLine(DynamicMatInstance);
	}
}

UAbilitySystemComponent* AEFDCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AEFDCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

UAnimMontage* AEFDCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}