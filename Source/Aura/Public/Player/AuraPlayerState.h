// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnplayerStatChange, int32); //StatValue

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	//LEVEL & XP
	FORCEINLINE int32 GetPlayerLevel() const {return PlayerLevel;}
	void SetLevel(int32 InLevel);
	void AddToLevel(int32 InLevel);
	
	FORCEINLINE int32 GetXP() const {return XP;}
	void SetXP(int32 InXP);
	void AddToXP(int32 InXP);

	
	FOnplayerStatChange OnLevelChange;

	FOnplayerStatChange OnXPChange;
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_PlayerLevel)
	int32 PlayerLevel = 1;
	
	UFUNCTION()
	void OnRep_PlayerLevel(int32 OldLevel);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing= OnRep_XP)
	int32 XP = 0;
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	
	
};
