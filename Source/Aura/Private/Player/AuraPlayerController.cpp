// Copyright Dark Sides


#include "Player/AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Inteactions/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates= true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
	
}
void AAuraPlayerController::AutoRun()
{
	if(!bAutoRunning) return;
	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction,1);
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	if(LastActor != ThisActor)
	{
		if(LastActor)
		{
			LastActor->UnHighLightActor();
		}
		if(ThisActor)
		{
			ThisActor->HighLightActor();
		}
	}
	
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
	
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//Release Any Button but not LMB
	if  (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetAuraAbilitySystemComponent()) GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		
		return;
	}
	//Releasing LMB And Targeting Enemy
	if(bTargeting)
	{
		if(GetAuraAbilitySystemComponent()) GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	}
	else 
	{
		//Short press LMB
		APawn* ControlledPawn = GetPawn();
		if(FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlledPawn->GetActorLocation(),CachedDestination);
			if(NavigationPath)
			{
				Spline->ClearSplinePoints();
				for(const FVector& PointLoc : NavigationPath->PathPoints)
				{
					//Adding Points from Navigation Path to Spline
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(),PointLoc, 8.f,8,FColor::Black,false,5.f);
				}
				CachedDestination = NavigationPath->PathPoints[NavigationPath->PathPoints.Num() - 1]; // reset Destination to the last point of the spline
				bAutoRunning = true;
				
			}
		}
	}
	//Reset time and boolean after releasing LMB
	FollowTime = 0.f;
	bTargeting = false;
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) // pressing any button but not the LMB
	{
		
		if(GetAuraAbilitySystemComponent()) GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		return;
	}
	if(bTargeting) //Holding LMB And Targeting Enemy
	{
		if(GetAuraAbilitySystemComponent())	GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		
	}
	else //only holding LMB Without Targeting Enemy (click to move)
	{
		FollowTime += GetWorld()->GetDeltaSeconds(); // start incrementing time
		
		if( CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.Location; // Store the new Location To move
		}
		
		if(APawn* ControlledPawn = GetPawn()) // getting pawn & Check it
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal(); // World Direction from pawn to destination location (Normalize)
			ControlledPawn->AddMovementInput(WorldDirection,1.f); //Add movement
		}
	}
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

