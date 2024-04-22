// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

/**
 * 
 */
class UGameplayEffect;
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior,
	Ranger,
	Elementalist
	
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	//Gameplay Effect to apply Primary Attributes
	UPROPERTY(EditDefaultsOnly, Category= "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	

	
};

UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//Gameplay Effect to apply Common Attributes
	UPROPERTY(EditDefaultsOnly, Category= "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	//Gameplay Effect to apply Vital Attributes
	UPROPERTY(EditDefaultsOnly, Category= "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category= "Character Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharacterClassInformation;


	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);



	
};
