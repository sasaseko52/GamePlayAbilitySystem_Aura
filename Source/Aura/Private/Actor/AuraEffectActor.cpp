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

	
	//get the t-shared pointer of data from effect spec struct then de-reference it by *
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
	
}



