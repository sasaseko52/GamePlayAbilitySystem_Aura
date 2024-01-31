// Copyright Dark Sides


#include "Character/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "Aura/Aura.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	
}

void AEnemyCharacter::HighLightActor()
{
	

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(Red_Custom_Depth);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(Red_Custom_Depth);
}

void AEnemyCharacter::UnHighLightActor()
{

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

	
}
