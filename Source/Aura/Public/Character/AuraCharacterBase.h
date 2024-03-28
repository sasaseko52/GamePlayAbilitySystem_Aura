// Copyright Dark Sides

#pragma once
#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inteactions/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter , public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void InitializeDefaultAttributes();
	void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass , float Level);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
