// Copyright Dark Sides

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);
UCLASS(BlueprintType , Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	
	virtual void BroadcastInitialValues()override;
	virtual void BindCallbackToDependencies()override;
	
	
	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
private:

	void BroadCastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute)const;
};
