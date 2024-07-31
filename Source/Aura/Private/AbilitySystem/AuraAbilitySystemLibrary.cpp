// Copyright Dark Sides


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AuraAbilityTypes.h"
#include "ToolContextInterfaces.h"
#include "Game/AuraGameModeBase.h"
#include "Inteactions/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	//Get Player Controller
	
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		//Get Hud 
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent =AuraPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);

			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	//Get Player Controller
	
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		//Get Hud 
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent =AuraPlayerState->GetAbilitySystemComponent();
			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);

			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
	
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	
	//initialize default Gameplay Effects to Self 
	//Apply Primary
	FGameplayEffectContextHandle PrimaryContextHandle =ASC->MakeEffectContext();
	PrimaryContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,PrimaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data);
	
	//Secondary
	FGameplayEffectContextHandle SecondaryContextHandle =ASC->MakeEffectContext();
	SecondaryContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SecondaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data);

	//Vital
	FGameplayEffectContextHandle VitalContextHandle =ASC->MakeEffectContext();
	VitalContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data);
	
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,ECharacterClass CharacterClass)
{
		
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if(CharacterClassInfo == nullptr) return;
	for(TSubclassOf<UGameplayAbility> Ability :CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& CharacterClassDefaultInfo =CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	for(TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassDefaultInfo.StartupAbilities)
	{
		ICombatInterface* CombatInterface =Cast<ICombatInterface>(ASC->GetAvatarActor());
		if(CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
		
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	//game mode links between AuraAbilitySystemLibrary and Character class info (Game Mode is Only Initialized On Server, Clients cannot Get it)
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(AuraGameMode == nullptr) return nullptr;
	
	return AuraGameMode->CharacterClassInfo;
	
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& ContextHandle)
{
	const FAuraGameplayEffectContext* AuraEffectContext= static_cast<const FAuraGameplayEffectContext*>(ContextHandle.Get());
	if(AuraEffectContext)
	{
			return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle)
{
	const FAuraGameplayEffectContext* AuraEffectContext= static_cast<const FAuraGameplayEffectContext*>(ContextHandle.Get());
	if(AuraEffectContext)
	{
		return AuraEffectContext->IsCriticalHit(); 
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& ContextHandle, bool bInIsBlockedHit)
{
	 FAuraGameplayEffectContext* AuraEffectContext= static_cast< FAuraGameplayEffectContext*>(ContextHandle.Get());
	if(AuraEffectContext)
	{
		 AuraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& ContextHandle, bool bInIsCriticalHit)
{
	FAuraGameplayEffectContext* AuraEffectContext= static_cast< FAuraGameplayEffectContext*>(ContextHandle.Get());
	if(AuraEffectContext)
	{
		AuraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	
	
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
	if(World)
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps,SphereOrigin,FQuat::Identity,FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),FCollisionShape::MakeSphere(Radius),SphereParams);	
		for(FOverlapResult& Overlap : Overlaps)
		{
			
			if(Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* First, AActor* Second)
{
			
	const bool BothArePlayers = First->ActorHasTag(FName("Player")) && Second->ActorHasTag(FName("Player"));
	const bool BothAreEnemies = First->ActorHasTag(FName("Enemy")) && Second->ActorHasTag(FName("Enemy"));

	const bool Friends = BothArePlayers || BothAreEnemies;
	
	return !Friends;
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(ECharacterClass CharacterClass, int32 Level, const UObject* WorldContextObject)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if(CharacterClassInfo == nullptr) return 0;
	
	FCharacterClassDefaultInfo Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	float XPReward = Info.XPReward.GetValueAtLevel(Level);

	return static_cast<int32>(XPReward);
}
