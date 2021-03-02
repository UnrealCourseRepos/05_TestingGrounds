// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/InputComponent.h"
#include "Weapons/Gun.h"



// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Component
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	//FP Arms
	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetupAttachment(FPCamera);
	FPArms->SetOnlyOwnerSee(true);
	FPArms->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	FPArms->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPArms->bCastDynamicShadow = false;
	FPArms->CastShadow = false;

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."))
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled()) {
		Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	Gun->AnimInstance1P = FPArms->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

	if(InputComponent != nullptr){
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AMannequin::PullTrigger() {
	Gun->OnFire();
}