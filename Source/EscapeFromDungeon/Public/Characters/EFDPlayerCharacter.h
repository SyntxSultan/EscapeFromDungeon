// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Characters/EFDCharacterBase.h"
#include "EFDPlayerCharacter.generated.h"


UCLASS()
class ESCAPEFROMDUNGEON_API AEFDPlayerCharacter : public AEFDCharacterBase
{
	GENERATED_BODY()
public:
	AEFDPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	virtual void InitAbilityActorInfo() override;
};
