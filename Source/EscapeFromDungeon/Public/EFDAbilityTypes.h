#pragma once
#include "GameplayEffectTypes.h"
#include "EFDAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FEFDGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	bool IsBlockedHit() const { return bIsBlocked; };
	bool IsCriticalHit() const { return bIsCritical; };

	void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCritical = bInIsCriticalHit; }
	void SetIsBlockedHit(const bool bInIsBlockedHit) { bIsBlocked = bInIsBlockedHit; }
	
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	virtual FEFDGameplayEffectContext* Duplicate() const
	{
		FEFDGameplayEffectContext* NewContext = new FEFDGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
protected:
	
	UPROPERTY()
	bool bIsBlocked = false;
	
	UPROPERTY()
	bool bIsCritical = false;
};

template<>
struct TStructOpsTypeTraits< FEFDGameplayEffectContext > : TStructOpsTypeTraitsBase2< FGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		
	};
};