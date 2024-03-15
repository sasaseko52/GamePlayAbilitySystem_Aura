// Copyright Dark Sides


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	//initial values of attributes
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	//Bind the Change of value to function that broadcast the new value from the attribute set to the Widget
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda
	(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for(const FGameplayTag& Tag : AssetTags)
			{
				
				//Specify Only Messages Tags in the Asset Tags Container
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				
				if(Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row =GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
				
			}
		}
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	//broadcast the new value from the attribute set to the Widget
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	//broadcast the new value from the attribute set to the Widget
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	//broadcast the new value from the attribute set to the Widget
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
