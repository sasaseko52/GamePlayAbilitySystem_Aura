// Copyright Dark Sides


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Inteactions/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	
	VigorDef.AttributeToCapture = UMyAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Storing any tags that source has in tag container
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	//Storing any tags that Target has in tag container
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Passing Tags on to structure in order to capture the attribute needed
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float VigorMagnitude = 0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluationParameters,VigorMagnitude);

	VigorMagnitude = FMath::Max<float>(VigorMagnitude, 0.f);

	ICombatInterface* CombatInterface =	Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	
	return 80.f + 2.5f * VigorMagnitude + 10.f * PlayerLevel;
	
}
