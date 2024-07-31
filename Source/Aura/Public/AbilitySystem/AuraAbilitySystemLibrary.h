// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"


class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category= "Aura ABility System Library|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category= "Aura ABility System Library|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|DefaultAttributes")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|DefaultAttributes")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass);
	
	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|CharacterClassDefault")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category= "Aura ABility System Library|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& ContextHandle);

	UFUNCTION(BlueprintPure, Category= "Aura ABility System Library|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle);

	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& ContextHandle,bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& ContextHandle,bool bInIsCriticalHit);
	
	UFUNCTION(BlueprintCallable, Category= "Aura ABility System Library|GameplayMechanics")
	static void GetLivePlayerWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Aura ABility System Library|GameplayMechanics")
	static bool IsNotFriend(AActor* First, AActor* Second);

	static int32 GetXPRewardForClassAndLevel(ECharacterClass CharacterClass, int32 Level, const UObject* WorldContextObject);
};
