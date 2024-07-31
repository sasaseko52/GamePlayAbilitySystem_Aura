// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Inteactions/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"

#include "EnemyCharacter.generated.h"

class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
class UWidgetComponent;
UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	
	/*Combat Interface*/

	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/*Combat Interface End*/

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;


	void OnHealthChangedCallBack(const FOnAttributeChangeData& Data);
	
	void OnMaxHealthChangedCallBack(const FOnAttributeChangeData& Data);

	void HitReactTagChanged(const FGameplayTag CallbackTag,int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	bool bHitReacting = false;
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category= "Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category= "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category= "Combat")
	TObjectPtr<AActor> CombatTarget;
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= " Charater Class Defaults")
	int32 Level = 1;
	
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	/*   //  AI  //  */
	UPROPERTY(EditAnywhere, Category= " AI ")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
	/* //  AI  //  End*/
	
private:
	
	
	


	
};
