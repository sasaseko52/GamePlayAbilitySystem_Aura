// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	

	
	void Move(const struct FInputActionValue& InputActionValue);

	void CursorTrace();

	TObjectPtr<IEnemyInterface> ThisActor;
	TObjectPtr<IEnemyInterface> LastActor;
	//input config
	UPROPERTY(EditDefaultsOnly, Category= "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;
	
	//Call Back Functions for Ability Input Actions

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	//Setting Aura Ability System Component
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent>AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
};
