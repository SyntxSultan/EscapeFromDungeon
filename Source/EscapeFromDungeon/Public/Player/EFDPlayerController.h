// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EFDPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEFDPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& Value);
	void CursorTrace();
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
};
