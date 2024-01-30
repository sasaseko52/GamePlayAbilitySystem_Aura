// Copyright Dark Sides


#include "Character/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "SNegativeActionButton.h"

AEnemyCharacter::AEnemyCharacter()
{
	
	
	
}

void AEnemyCharacter::HighLightActor()
{
	
	DrawDebugSphere(GetWorld(),GetActorLocation(),50,24,FColor::Red,false,15,0,2);
	UE_LOG(LogTemp,Warning,TEXT("ssssss"));
}

void AEnemyCharacter::UnHighLightActor()
{




	
}
