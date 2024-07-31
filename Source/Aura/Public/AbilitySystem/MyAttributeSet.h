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


USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){};
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	//Source info
	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	//Taregt info
	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//typedef specific to the FGameplayAttribute() signature, but TStaticFuncPtr is generic to any signature

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class AURA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMyAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// make an opportunity to make calculation before changing attribute numerical values such as clamping
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	//
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	//Map to connect game play tags to attribute delegates
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

		
	/*Primary Attributes*/
	//Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category= "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Strength)
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength)const;
	
	//Intilligence
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	//Resilience
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	//Vigor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	/*Secondary Attributes*/
	// Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category= "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Armor)
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor)const;
	
	// ArmorPenetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category= "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,ArmorPenetration)
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration)const;
	
	// BlockChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category= "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,BlockChance)
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)const;

	// CriticalHitChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category= "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitChance)
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)const;

	// CriticalHitDamage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category= "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitDamage)
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage)const;

	// CriticalHitResistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category= "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,CriticalHitResistance)
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance)const;

	// HealthRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category= "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,HealthRegeneration)
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)const;

	// ManaRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category= "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,ManaRegeneration)
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)const;
	
	//Max Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category= "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//Max Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category= "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	/* Vital Attribute*/
	//Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category= "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	//Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category= "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	
	/* Meta Attributes*/
	//Damage  meta Attribute
	UPROPERTY(BlueprintReadOnly, Category= "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,IncomingDamage);


	UPROPERTY(BlueprintReadOnly, Category= "Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,IncomingXP);
	
	/* Resistance Attributes*/

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_FireResistance,Category= "Resistacne Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,FireResistance);
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_LightingResistance,Category= "Resistacne Attributes")
	FGameplayAttributeData LightingResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,LightingResistance);
	UFUNCTION()
	void OnRep_LightingResistance(const FGameplayAttributeData& OldLightingResistance) const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_ArcaneResistance,Category= "Resistacne Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,ArcaneResistance);
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_PhysicalResistance,Category= "Resistacne Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet,PhysicalResistance);
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance)const;

	

	
private:
	//Handel effect properties
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	
	void ShowFloatingText(const FEffectProperties& Props,float DamageText, bool bBlockedHit, bool bCriticalHit);

	void SendXPEvent(const FEffectProperties& Props);
};
