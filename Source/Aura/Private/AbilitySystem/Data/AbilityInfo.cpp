// Copyright Dark Sides


#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bNotFound)
{

	for(FAuraAbilityInfo Info : AbilityInformation)
	{
		if(Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if(bNotFound)
	{
		UE_LOG(LogAura,Error,TEXT("Cant Find Info for Ability Tag in Ability Info Struct [%s]"),*AbilityTag.ToString());
	}
	return FAuraAbilityInfo();
}
