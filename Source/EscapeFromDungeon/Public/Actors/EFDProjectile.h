// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EFDProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AEFDProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
