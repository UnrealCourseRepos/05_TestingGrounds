// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "NavMeshBoundsVolume.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool() {

	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator) {
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd) {

	NavMeshBoundsVolumePool->AddActor(VolumeToAdd);
	//UE_LOG(LogTemp, Warning, TEXT("Nav Mesh found: %s"), *VolumeToAdd->GetName());
}

void AInfiniteTerrainGameMode::NewTileConquered()
{
	Score++;
}

int AInfiniteTerrainGameMode::GetScore()
{
	return Score;
}


