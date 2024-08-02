// Copyright SyntaxSultan


#include "Actors/EFDEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "Components/SphereComponent.h"

AEFDEffectActor::AEFDEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AEFDEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEFDEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEFDEffectActor::EndOverlap);
}

void AEFDEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TScriptInterface<IAbilitySystemInterface> ASCInterface = OtherActor)
	{
		const UEFDAttributeSet* EFDAttributeSet = Cast<UEFDAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UEFDAttributeSet::StaticClass()));
		UEFDAttributeSet* MutableAttributeSet = const_cast<UEFDAttributeSet*>(EFDAttributeSet);
		MutableAttributeSet->SetHealth(MutableAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AEFDEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
