// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EFDAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEFDAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
