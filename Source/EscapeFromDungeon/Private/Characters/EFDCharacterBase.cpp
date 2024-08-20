// Copyright SyntaxSultan


#include "Characters/EFDCharacterBase.h"

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

void AEFDCharacterBase::InitAbilityActorInfo()
{
	
}
