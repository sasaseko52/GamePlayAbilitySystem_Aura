// Copyright Dark Sides


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("EffectActorMesh");
	SetRootComponent(Mesh);
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);

	

}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: change this to apply a gameplay effect
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMyAttributeSet* AuraAttributeSet = Cast<UMyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMyAttributeSet::StaticClass()));
		UMyAttributeSet* MuatableAuraAttributeSet= const_cast<UMyAttributeSet*>(AuraAttributeSet);
		MuatableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 50.f);
		Destroy();
	}

	
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	

	
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::OnEndOverlap);
}



