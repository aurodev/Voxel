// Copyright 2017 Phyronnaz

#include "VoxelInvokerComponent.h"
#include "Components/PrimitiveComponent.h"
//#include "Engine.h"


UVoxelInvokerComponent::UVoxelInvokerComponent() : bNeedUpdate(true), DistanceOffset(1000)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVoxelInvokerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bNeedUpdate)
	{
		if (true || GetNetMode() < ENetMode::NM_Client || (Cast<APawn>(GetOwner()) && Cast<APawn>(GetOwner())->Role == ROLE_AutonomousProxy))
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVoxelWorld::StaticClass(), FoundActors);

			if (FoundActors.Num() == 0)
			{
				UE_LOG(LogVoxel, Warning, TEXT("No world found"));
			}
			else
			{
				for (auto Actor : FoundActors)
				{
					((AVoxelWorld*)Actor)->AddInvoker(TWeakObjectPtr<UVoxelInvokerComponent>(this));
				}
			}
		}
		bNeedUpdate = false;
	}
}
