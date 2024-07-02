// Copyright Dark Sides


#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "AuraGameplayTags.h"
#include "Inteactions/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation,  const FGameplayTag& SocketTag , bool bOverridePitch , float PitchOverride)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;

	//Getting the avatar actor of this ability then cast it to Combat interface 
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	
	//get weapon socket location to spawn projectile
	if(CombatInterface)
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

		// if We Want to Override Projectile Pitch 
		if(bOverridePitch)
		{
			Rotation.Pitch = PitchOverride;
		}
				
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set Rotation
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AAuraProjectile* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform,GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//Giving Projectile Effect Spec for causing Damage 
		const UAbilitySystemComponent* SourceAbilitySystemComponent= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		//SetEffectProperties() in AttributeSet
		FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystemComponent->MakeEffectContext();
	
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(SpawnedProjectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(SpawnedProjectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		EffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle SpecHandle = SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),EffectContextHandle);
		
		for(TPair<FGameplayTag,FScalableFloat> DamagePair : DamageType)
		{
			const float ScaledDamage = DamagePair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DamagePair.Key,ScaledDamage);
		}
		
		SpawnedProjectile->DamageEffectSpecHandle = SpecHandle;
		
		SpawnedProjectile->FinishSpawning(SpawnTransform);
	}
}
