// Copyright SyntaxSultan


#include "Characters/EFDEnemyCharacter.h"

#include "EFDGameplayTags.h"
#include "AbilitySystem/EFDAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "EscapeFromDungeon/EscapeFromDungeon.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	UEFDAbilitySystemBlueprintLibrary::GiveStartupAbilities(this, AbilitySystemComponent);

	if (UEFDUserWidget* EFDUserWidget = Cast<UEFDUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		EFDUserWidget->SetWidgetController(this);	
	}
	
	if (const UEFDAttributeSet* EFDAttributeSet = Cast<UEFDAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(FEFDGameplayTags::Get().Effects_HitReact).AddUObject(this, &AEFDEnemyCharacter::HitReactTagChanged);
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

void AEFDEnemyCharacter::InitializeDefaultAttributes() const
{
	UEFDAbilitySystemBlueprintLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AEFDEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
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

void AEFDEnemyCharacter::Die()
{
	SetLifeSpan(LifeSpanAfterDeath);
	Super::Die();
}
