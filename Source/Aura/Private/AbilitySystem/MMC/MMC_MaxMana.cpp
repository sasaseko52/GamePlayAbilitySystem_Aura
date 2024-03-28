// Copyright Dark Sides


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/MyAttributeSet.h"
#include "Inteactions/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UMyAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Source tags into container
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	//Target tags into Container
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float IntelligenceMagnitude = 0.f;
	
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,IntelligenceMagnitude);

	IntelligenceMagnitude = FMath::Max<float>(IntelligenceMagnitude,0.f);

	ICombatInterface* CombatInterface =Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50 + 2 * IntelligenceMagnitude + 5 * PlayerLevel;
}
