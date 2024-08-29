// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "EFDAssetManager.generated.h"


UCLASS()
class ESCAPEFROMDUNGEON_API UEFDAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static const UEFDAssetManager& Get();
	virtual void StartInitialLoading() override;
};
