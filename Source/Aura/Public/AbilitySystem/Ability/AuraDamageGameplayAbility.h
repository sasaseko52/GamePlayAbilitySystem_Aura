// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "Inteactions/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"



/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap <FGameplayTag, FScalableFloat> DamageType;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomMontage(const TArray<FTaggedMontage>& TaggedMontages)const;
};
