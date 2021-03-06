// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

AActor* UActorPool::Checkout() {
	//UE_LOG(LogTemp, Warning, TEXT("CAT: [%s] Checkout"), *GetName()); //TODO Remove
	if (Pool.Num() == 0) {
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::ReturnActor(AActor* ActorToReturn) {
	AddActor(ActorToReturn);
}

void UActorPool::AddActor(AActor* ActorToAdd) {
	Pool.Push(ActorToAdd);
}

