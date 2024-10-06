// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Characters/EFDCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EFDEnemyCharacter.generated.h"


class UWidgetComponent;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDEnemyCharacter : public AEFDCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEFDEnemyCharacter();
	
	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// End Enemy Interface
	/* Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	/* End Combat Interface*/

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(EditDefaultsOnly)
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float LifeSpanAfterDeath = 5.f;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Ranger;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

};
