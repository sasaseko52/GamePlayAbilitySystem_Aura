// Copyright Dark Sides


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	//check if the ptr has ability system component
	if(TargetAbilitySystemComponent == nullptr) return;
	
	check(GameplayEffectClass);
	
	// wrapper that contain game  play effects data
	FGameplayEffectContextHandle EffectContextHandle =  TargetAbilitySystemComponent->MakeEffectContext();
	
	//Store data about this effect
	EffectContextHandle.AddSourceObject(this);
	
	//make  spec handle in the blueprint to apply this effect to different targets in the multiple times
	const FGameplayEffectSpecHandle EffectSpec = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);

	
	//get the t-shared pointer of data from effect spec struct then de-reference it by * then store it in a struct and (Apply it to target)
	 FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
	
	//check the duration type if its infinite or not
	bool bIsInfinite = EffectSpec.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;

	//if the duration type is infinite , store its struct & target ability system component in a T Map
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		 ActiveEffectHandles.Add(ActiveEffectHandle,TargetAbilitySystemComponent);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		
		if(!IsValid(TargetAbilitySystemComponent)) return;
		
		//Array to add in the effect handles we want to remove from TMap
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		//checking the Tmap Pairs to find which one is equal to our ability system component
		for(TTuple<FActiveGameplayEffectHandle,UAbilitySystemComponent*>  HandlePair : ActiveEffectHandles )
		{
			if( TargetAbilitySystemComponent == HandlePair.Value )
			{
				//first Remove the Gameplay Effect from the Ability System Component
				TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				
				//Add the Game play Effect to the removal Array
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		//find that game play effect (Pair) and remove it from the T-map 
		for(FActiveGameplayEffectHandle& Handle :HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}



