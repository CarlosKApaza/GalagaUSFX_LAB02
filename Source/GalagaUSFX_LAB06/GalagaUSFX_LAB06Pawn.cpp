// Copyright Epic Games, Inc. All Rights Reserved.

#include "GalagaUSFX_LAB06Pawn.h"
#include "GalagaUSFX_LAB06Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

#include "BuilderPortaNavesAereasNiv1.h"
#include "PortaNavesAereas.h"
#include "GalagaUSFX_LAB06GameMode.h"


const FName AGalagaUSFX_LAB06Pawn::MoveForwardBinding("MoveForward");
const FName AGalagaUSFX_LAB06Pawn::MoveRightBinding("MoveRight");
const FName AGalagaUSFX_LAB06Pawn::FireForwardBinding("FireForward");
const FName AGalagaUSFX_LAB06Pawn::FireRightBinding("FireRight");

AGalagaUSFX_LAB06Pawn::AGalagaUSFX_LAB06Pawn()
{	
	// Asignar los valores a PosicionPortaNaveAerea
	//PosicionPortaNaveAerea = FVector(-1080.0f, 1650.0f, 160.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("SoundWave'/Game/AudioShot/laser-gun-shot-sound-future-sci-fi-lazer-wobble-chakongaudio-174883.laser-gun-shot-sound-future-sci-fi-lazer-wobble-chakongaudio-174883'"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
	//MaxProjectiles = 30; // Inicializar MaxProjectiles aquí
}

void AGalagaUSFX_LAB06Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AGalagaUSFX_LAB06Pawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	//// INTENTA DISPARAR SI HAY PROYECTILES DISPONIBLES
	//if (NumProjectilesFired < MaxProjectiles) // Si el número de proyectiles disparados es menor al máximo de proyectiles
	//{
	//	FireShot(FireDirection); // Disparar
	//}

	// Try and fire a shot
	FireShot(FireDirection);
}

void AGalagaUSFX_LAB06Pawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AGalagaUSFX_LAB06Projectile>(SpawnLocation, FireRotation);
				//NumProjectilesFired++; // Incrementar el número de proyectiles disparados.
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalagaUSFX_LAB06Pawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AGalagaUSFX_LAB06Pawn::ShotTimerExpired()
{
	bCanFire = true;
}
//
//void AGalagaUSFX_LAB06Pawn::RecargarBalasSiEnPosicionCorrecta()
//{
//	FVector PosicionActual = GetActorLocation();
//	const float DistanciaUmbral = 200.0f; // Puedes ajustar esta distancia según sea necesario
//	if ((PosicionActual - PosicionPortaNaveAerea).SizeSquared() <= FMath::Square(DistanciaUmbral)) { // Verifica si la nave está cerca de la posición del hangar
//		ABuilderPortaNavesAereasNiv1* Builder = GetWorld()->SpawnActor<ABuilderPortaNavesAereasNiv1>(); // Crea una instancia del builder
//		if (Builder) {
//			Builder->ConstruirRecargarMuniciones(); // Llama al método del builder para recargar municiones
//			UE_LOG(LogTemp, Warning, TEXT("Municiones recargadas en el hangar."));
//
//			// Configura un temporizador para recargar automáticamente después de un tiempo
//			const float TiempoRecargaAutomatica = 20.0f; // Ajusta este valor según sea necesario
//			GetWorldTimerManager().SetTimer(TimerHandle_RecargaAutomatica, this, &AGalagaUSFX_LAB06Pawn::RecargarAutomaticamente, TiempoRecargaAutomatica, false);
//		}
//		else {
//			UE_LOG(LogTemp, Error, TEXT("No se pudo obtener el Builder para recargar municiones."));
//		}
//	}
//}

//void AGalagaUSFX_LAB06Pawn::RecargarAutomaticamente()
//{
//	// Recarga automáticamente después de un tiempo
//	RecargarBalasSiEnPosicionCorrecta();
//}
