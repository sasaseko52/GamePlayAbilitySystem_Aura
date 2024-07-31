
#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
	int32 Level = 1;
	bool bSearching = true;
	while(bSearching)
	{
		//LevelUpInfos[0] = No Information
		//LevelUpInfos[1] = Level 1 Information
		//LevelUpInfos[2] = Level 2 Information
		if(LevelUpInfos.Num() - 1 <= Level) return Level;
		
		if(XP >= LevelUpInfos[Level].LevelUpRequirement)
		{
			//if XP is greater than level Up Requirement ( Add One more Level)
			++Level;
		}
		else
		{
			bSearching = false;
		}
		
	}

	return Level;
}
