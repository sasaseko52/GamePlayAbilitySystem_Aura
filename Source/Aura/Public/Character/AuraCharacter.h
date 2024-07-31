// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Inteactions/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase , public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	/*Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	/*Combat Interface End*/

	/*Player Interface*/

	virtual void AddToXP_Implementation(int32 InXP) override;
	
	/*Player Interface ends*/
private:
	virtual void InitAbilityActorInfo() override;
};
