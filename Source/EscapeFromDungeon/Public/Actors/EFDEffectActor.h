// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EFDEffectActor.generated.h"

class USphereComponent;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEFDEffectActor();
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
