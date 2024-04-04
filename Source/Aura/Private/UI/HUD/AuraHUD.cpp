// Copyright Dark Sides


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		
		//Bind callbacks to the widget for the sake of passing new values if changed to the overlay widget
		OverlayWidgetController->BindCallbackToDependencies();
		
	}
	return OverlayWidgetController;
	
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		
		AttributeMenuWidgetController->BindCallbackToDependencies();
		
	}
	return  AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class UnInitialized, please fill out bp aura HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class UnInitialized , please fill out bp aura HUD"));

	//create overlay widget
	UUserWidget* Widget	= CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	//create widget controller params struct
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	
	//create widget controller and assign its params for the overlay widget
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	//Set controller for the overlay widget
	OverlayWidget->SetWidgetController(WidgetController);
	
	//broad cast delegate for initial values
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();

	
}

