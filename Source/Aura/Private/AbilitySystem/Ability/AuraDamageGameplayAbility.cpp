// Copyright Dark Sides


#include "AbilitySystem/Ability/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass,1);
	for(TTuple <FGameplayTag,FScalableFloat> DamagePair : DamageType)
	{
		const float DamageMagnitude = DamagePair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DamagePair.Key,DamageMagnitude);
		
	}
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),TargetASC);
	
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomMontage(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if(TaggedMontages.Num() > 0)
	{
		 int32 Selection = FMath::RandRange(0, TaggedMontages.Num()-1);
		
		return TaggedMontages[Selection];
	}


	return FTaggedMontage();
	
}
