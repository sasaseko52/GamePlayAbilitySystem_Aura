// Copyright Dark Sides


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	//Calling initialization Function from C++ Native class AuraGameplayTags
	FAuraGameplayTags::InitializeNativeGameplayTags();

	//UAbilitySystemGlobals::InitGlobalsData(); only in (UE 5.1)


	
}
