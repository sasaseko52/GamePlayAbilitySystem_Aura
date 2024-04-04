// Copyright Dark Sides


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for(auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		BroadCastAttributeInfo(Pair.Key,Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbackToDependencies()
{
	UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	for(auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadCastAttributeInfo(Pair.Key,Pair.Value());
		}
		);
	}
	
}

void UAttributeMenuWidgetController::BroadCastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
