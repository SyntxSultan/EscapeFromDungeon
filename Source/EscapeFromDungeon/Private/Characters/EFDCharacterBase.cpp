// Copyright SyntaxSultan


#include "Characters/EFDCharacterBase.h"

AEFDCharacterBase::AEFDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEFDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
