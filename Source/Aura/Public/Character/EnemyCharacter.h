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
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	
	/*Combat Interface*/

	virtual int32 GetPlayerLevel() override;
	/*Combat Interface End*/
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= " Charater Class Defaults")
	int32 Level = 1;
private:
	
	
	


	
};
