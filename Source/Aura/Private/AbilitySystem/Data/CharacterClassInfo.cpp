// Copyright Dark Sides


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{

	//give info specified with each character class enum
	return CharacterClassInformation.FindChecked(CharacterClass);	
	
}
