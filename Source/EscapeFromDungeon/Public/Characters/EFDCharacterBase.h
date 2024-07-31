// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EFDCharacterBase.generated.h"

UCLASS(Abstract)
class ESCAPEFROMDUNGEON_API AEFDCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEFDCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
