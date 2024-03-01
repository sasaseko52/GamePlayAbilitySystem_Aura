// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraEffectActor();
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(BLueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
		
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
private:
	

};
