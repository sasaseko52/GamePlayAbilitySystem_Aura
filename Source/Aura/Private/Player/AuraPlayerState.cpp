// Copyright Dark Sides


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;
		
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystem");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraPlayerState,PlayerLevel);
	DOREPLIFETIME(AAuraPlayerState,XP);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAuraPlayerState::SetLevel(int32 InLevel)
{
	PlayerLevel = InLevel;
	OnLevelChange.Broadcast(PlayerLevel);
}
void AAuraPlayerState::AddToLevel(int32 InLevel)
{
	PlayerLevel += InLevel;
	OnLevelChange.Broadcast(PlayerLevel);
}
void AAuraPlayerState::OnRep_PlayerLevel(int32 OldLevel)
{
	OnLevelChange.Broadcast(PlayerLevel);
}

void AAuraPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChange.Broadcast(XP);
}

void AAuraPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChange.Broadcast(XP);
}



void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChange.Broadcast(XP);

	
}	
