// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"


UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};


class AURA_API IEnemyInterface
{
	GENERATED_BODY()


public:
	virtual void HighLightActor() = 0;
	virtual void UnHighLightActor() = 0;
	
	
};