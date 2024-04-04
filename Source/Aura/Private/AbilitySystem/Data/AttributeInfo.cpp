// Copyright Dark Sides


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for(const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
			
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp , Error, TEXT("Cant find info for attribute tag [%s] on attribute info [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
