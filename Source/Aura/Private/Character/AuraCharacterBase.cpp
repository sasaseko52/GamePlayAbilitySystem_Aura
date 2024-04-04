// Copyright Dark Sides

#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	
return  AbilitySystemComponent;
	
}


void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitializeDefaultAttributes()
{
	ApplyGameplayEffectToSelf(DefaultPrimaryAttributes,1.f);
	ApplyGameplayEffectToSelf(DefaultSecondaryAttributes,1.f);
	ApplyGameplayEffectToSelf(DefaultVitalAttributes,1.f);
}


void AAuraCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GamePlayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data,GetAbilitySystemComponent());
}

void AAuraCharacterBase::AddCharacterAbilties()
{
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	if(!HasAuthority())return;
	AuraAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
	
	
	
}


