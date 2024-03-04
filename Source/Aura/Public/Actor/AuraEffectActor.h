// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;


UENUM(BlueprintType)
enum class EEffectApplicationPolicy 
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

//applied only for infinite game play effects
UENUM(BlueprintType)
enum class EEffectRemovalPolicy 
{
	RemoveOnEndOverlap,
	DoNotRemove
};

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
	
	UFUNCTION(BLueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BLueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	bool bDestroyOnEffectRemoval = false;
	// game play effects 
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	//Infinite
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Applied Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	
	//Policies for Effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Effect Application Policy")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Effect Application Policy")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	//Policies for Infinite Effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Effect Application Policy")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Effect Application Policy")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
	

};
