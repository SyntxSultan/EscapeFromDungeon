// Copyright SyntaxSultan


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "EFDAbilityTypes.h"
#include "EFDGameplayTags.h"
#include "AbilitySystem/EFDAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "Interaction/CombatInterface.h"

struct EFDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	EFDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, ArcaneResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEFDAttributeSet, PhysicalResistance, Target, false);
		
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Resistance_Arcane, ArcaneResistanceDef);
		TagsToCaptureDefs.Add(FEFDGameplayTags::Get().Attributes_Resistance_Physical, PhysicalResistanceDef);
	}
};

static const EFDDamageStatics& DamageStatics()
{
	static EFDDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	AActor* SourceAvatar = ExecutionParams.GetSourceAbilitySystemComponent()->GetAvatarActor();
	AActor* TargetAvatar = ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor();

	TScriptInterface<ICombatInterface> SourceCombatInterface = SourceAvatar;
	TScriptInterface<ICombatInterface> TargetCombatInterface = TargetAvatar;
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const UCharacterClassInfo* CharacterClassInfo = UEFDAbilitySystemBlueprintLibrary::GetCharacterClassInfo(SourceAvatar);

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	FEFDGameplayEffectContext* EFDContext = static_cast<FEFDGameplayEffectContext*>(Spec.GetContext().Get());
	
	//Get Damage Set by Caller and reduce 1 percent of damage for every resistance point
	float Damage = 0.f;
	for (const auto& Pair : FEFDGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = EFDDamageStatics().TagsToCaptureDefs[Pair.Value];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);
		
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition, EvaluateParams, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;
		Damage += DamageTypeValue;
	}
	
	/* Capture BlockChance on Target and determine if there was successful Block */
	
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParams, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	EFDContext->SetIsBlockedHit(bBlocked);
	
	Damage = bBlocked ? Damage / 2.f : Damage;

	/* Armor & ArmorPen */
	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParams, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	float SourceArmorPen = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParams, SourceArmorPen);
	SourceArmorPen = FMath::Max<float>(0.f, SourceArmorPen);

	const FRealCurve* ArmorPenCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenCoefficient = ArmorPenCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//Armor Penetration ignores a percentage of target armor
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPen * ArmorPenCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	//Armor ignores a percentage of incoming damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	/* Critical Hit */
	
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParams, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParams, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParams, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	UEFDAbilitySystemBlueprintLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);
	
	//Double damage plus a bonus if critical hit
	Damage = bCriticalHit ? 2.f * Damage + SourceCriticalHitDamage : Damage;
	
	
	const FGameplayModifierEvaluatedData EvaluatedData(UEFDAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
