// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Characters/EFDCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EFDEnemyCharacter.generated.h"


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
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
};
