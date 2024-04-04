// Copyright Dark Sides


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Inteactions/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates= true;

	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();

	
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if(LastActor == nullptr) // last Actor is not valid
	{
		if(ThisActor !=nullptr) //This Actor is valid
		{
			ThisActor->HighLightActor();
			
		}
	}
	else //last Actor is valid
	{
		if(ThisActor == nullptr)
		{
			LastActor->UnHighLightActor();
		}
		else // both actor are valid
		{
			if(LastActor != ThisActor) // both valid but not the same enemy
			{
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
						
		}
	}
	
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Black,*InputTag.ToString());
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetAuraAbilitySystemComponent() == nullptr) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetAuraAbilitySystemComponent() == nullptr) return;
	GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); /// checking if this ptr is valid before player the game
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}


	DefaultMouseCursor = EMouseCursor::Hand;
	bShowMouseCursor = true;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
	AuraInputComponent->BindAbilityAction(InputConfig,this,&AAuraPlayerController::AbilityInputTagPressed,&AAuraPlayerController::AbilityInputTagReleased,&AAuraPlayerController::AbilityInputTagHeld);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);												//Fwd & Bwd in the y component of W S keys
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);													//right & left in the y component of A D keys
	}

	
	
}

