// Copyright Dark Sides


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	//initial values of attributes
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	//Bind XP Change delegate to call back
	 AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChange.AddUObject(this,&UOverlayWidgetController::OnXPChange);
	
	//
	const UMyAttributeSet* AuraAttributeSet = CastChecked<UMyAttributeSet>(AttributeSet);
	//Bind the Change of value to function that broadcast the new value from the attribute set to the Widget
	//Bind Health call back
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	//Bind Max Health call back
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	//Bind Mana Call Back
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	//Bind Max Mana Call Back
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if(UAuraAbilitySystemComponent* AuraAsc =	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if(AuraAsc->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraAsc);
		}
		else
		{
			AuraAsc->AbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::OnInitializeStartupAbilities);
		}
			
		
		//Bind Gameplay Tags Call backs
		AuraAsc->EffectAssetTags.AddLambda
		(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for(const FGameplayTag& Tag : AssetTags)
				{
				
					//Specify Only Messages Tags in the Asset Tags Container
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				
					if(Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row =GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				
				}
			}
		);
	}
	
	
	
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	// Get Info About All Given Abilities
	if(!AuraAbilitySystemComponent->bStartupAbilitiesGiven)return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this,AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraAbilityInfo Info=AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
		
	});
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChange(int32 NewXP)
{
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	ULevelUpInfo* LevelUpInfo= AuraPlayerState->LevelUpInfo;
	checkf(LevelUpInfo,TEXT(" Unable to find level up info, please fill out Auraplayer State"));

	int32 CurrentLevel =LevelUpInfo->FindLevelForXP(NewXP);
	int32 MaxLevel = LevelUpInfo->LevelUpInfos.Num();

	if(CurrentLevel <= MaxLevel && CurrentLevel > 0)
	{
		int32 LevelUpRequirement = LevelUpInfo->LevelUpInfos[CurrentLevel].LevelUpRequirement;
		int32 PreviousLevelRequirement = LevelUpInfo->LevelUpInfos[CurrentLevel- 1].LevelUpRequirement;
		int32 DeltaLevelUpRequirement = LevelUpRequirement - PreviousLevelRequirement;
		int32 XPForThisLevel = NewXP - PreviousLevelRequirement;
		
		float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelUpRequirement);
		OnXPChanged.Broadcast(XPBarPercent);
		
	}
	
}

