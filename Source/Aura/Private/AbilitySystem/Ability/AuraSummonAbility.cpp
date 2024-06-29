// Copyright Dark Sides


#include "AbilitySystem/Ability/AuraSummonAbility.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	
	//Splitting the Angel of Spawn Spread into parts depends of num of Minions
	const float DeltaSpread = SpawnSpread / NumMinions;
	
	//Main Rotation of the Spawn line (45d from the Forward Direction)
	const FVector LeftOfSpread =Forward.RotateAngleAxis(-SpawnSpread/2, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	for(int32 i = 0; i < NumMinions; i++)
	{
		// Multiple Rotations in the 45d (Cut into parts depends on the NumMinions)
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance,MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, ChosenSpawnLocation + FVector(0.f,0.f, 400.f), ChosenSpawnLocation - FVector(0.f,0.f, 400.f),ECC_Visibility);
		if(HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
			
		}
		SpawnLocations.Add(ChosenSpawnLocation);
			
	}
	
	
	
	
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0,MinionClasses.Num()-1);
	
	return MinionClasses[Selection];
}
