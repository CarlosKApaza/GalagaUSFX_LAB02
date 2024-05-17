// Fill out your copyright notice in the Description page of Project Settings.


#include "PortaNavesAereas.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
APortaNavesAereas::APortaNavesAereas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaPortaNave(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	// Create the mesh component
	MallaPortaNave = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	MallaPortaNave->SetStaticMesh(mallaPortaNave.Object);
	MallaPortaNave->SetupAttachment(RootComponent);


	// Inicializamos NumBalas y MaxBalas a algún valor
	NumBalas = 0;
	MaxBalas = 100; // Número máximo de balas permitidas
}

// Called when the game starts or when spawned
void APortaNavesAereas::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortaNavesAereas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortaNavesAereas::SetHangar(FString _hangar)
{
	Hangar = _hangar;
}

void APortaNavesAereas::SetCentrodeMuniciones(FString _Municiones)
{
	CentroMuniciones = _Municiones;
}

void APortaNavesAereas::SetCentrodeEscudos(FString _escudos)
{
	Escudos = _escudos;
}

void APortaNavesAereas::CaracteristicasPortaNaveAerea()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::Printf(TEXT("Se creo la PortaNaveAerea - Hangar %s"), *Hangar));
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::Printf(TEXT("Puedes Recargar Municiones en el Hangar %s"), *CentroMuniciones));
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, FString::Printf(TEXT("Puedes comprar un Escudo Americano, cuesta 100 monedas %s"), *Escudos));
}

void APortaNavesAereas::RecargarBalas(int32 NumBalasRecargar)
{
	// Asegúrate de que el número de balas no exceda el máximo
	NumBalas = FMath::Clamp(NumBalas + NumBalasRecargar, 0, MaxBalas);
}

