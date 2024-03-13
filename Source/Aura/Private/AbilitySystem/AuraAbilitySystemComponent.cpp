

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::OnEffectApplied);
		
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	for(const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("%s"),  *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black,Msg);
	}
	
}
