// Copyright SyntaxSultan


#include "Characters/EFDEnemyCharacter.h"

#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "EscapeFromDungeon/EscapeFromDungeon.h"
#include "UI/Widgets/EFDUserWidget.h"

AEFDEnemyCharacter::AEFDEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UEFDAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UEFDAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEFDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (UEFDUserWidget* EFDUserWidget = Cast<UEFDUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		EFDUserWidget->SetWidgetController(this);	
	}
	
	if (const UEFDAttributeSet* EFDAttributeSet = Cast<UEFDAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

		/* Broadcast initial values */
		OnHealthChanged.Broadcast(EFDAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(EFDAttributeSet->GetMaxHealth());
	}
}

void AEFDEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UEFDAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void AEFDEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEFDEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AEFDEnemyCharacter::GetPlayerLevel()
{
	return Level;
}
