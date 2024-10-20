// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EFDGameModeBase.generated.h"


class UCharacterClassInfo;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
