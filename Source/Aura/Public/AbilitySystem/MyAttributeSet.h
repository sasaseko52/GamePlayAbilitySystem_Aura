// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class AURA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	//Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category= "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//Max Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category= "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category= "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//Max Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category= "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	//Damage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Damage);
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldDamage);
};
