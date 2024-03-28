// Copyright Dark Sides


#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"

UMyAttributeSet::UMyAttributeSet()
{
	
	

	
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	//Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	
	//Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if(Attribute == GetHealthAttribute())
	{
		NewValue =FMath::Clamp(NewValue, 0 , GetMaxHealth());
	}
	
	if(Attribute == GetManaAttribute())
	{
		NewValue =FMath::Clamp(NewValue, 0 , GetMaxMana());
	}
}
void UMyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	//source  = causer of the effect , target = target of th effect (owner of this attribute set)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	//Get Source Info ( AvatarActor , Controller, Character and Ability System Component)
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetInstigatorAbilitySystemComponent();
	
	if(IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = 	Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	
	//Get Target Info ( AvatarActor , Controller, Character and Ability System Component)
	if(Data.Target.AbilityActorInfo.IsValid() &&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProps;
	SetEffectProperties(Data, EffectProps);
	
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0.f,GetMaxMana()));
	}
	
}

void UMyAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Strength,OldStrength);
}


void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//informing ability system that we are replicating a value
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Health, OldHealth);
	
	
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldMaxHealth);
	
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Mana,OldMana);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,MaxMana,OldMaxMana);
}

void UMyAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Intelligence,OldIntelligence);
}

void UMyAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Resilience,OldResilience);
}

void UMyAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Vigor,OldVigor);
}

void UMyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,Armor,OldArmor);	
}

void UMyAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UMyAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,BlockChance,OldBlockChance);
}

void UMyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UMyAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UMyAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UMyAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UMyAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet,ManaRegeneration,OldManaRegeneration);
}





