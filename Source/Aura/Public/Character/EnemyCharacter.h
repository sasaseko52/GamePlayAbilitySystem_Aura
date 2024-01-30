// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Inteactions/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

protected:
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;

	
};
