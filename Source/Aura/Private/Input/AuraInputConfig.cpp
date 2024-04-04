// Copyright Dark Sides


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const FAuraInputAction& Action : AbilityInputActions )
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Error in Ability Input Actions or -NOT FOUND_"));
	}
	
	return nullptr;
}
