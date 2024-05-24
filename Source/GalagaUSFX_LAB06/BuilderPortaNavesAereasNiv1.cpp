// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderPortaNavesAereasNiv1.h"
#include "PortaNavesAereas.h"

#include "Hangar.h"
#include "CentroMuniciones.h"
#include "Escudo.h"
#include "Motor.h"

// Sets default values
ABuilderPortaNavesAereasNiv1::ABuilderPortaNavesAereasNiv1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilderPortaNavesAereasNiv1::BeginPlay()
{
	Super::BeginPlay();
	PortaNaveAerea = GetWorld()->SpawnActor<APortaNavesAereas>(APortaNavesAereas::StaticClass());
	PortaNaveAerea->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ABuilderPortaNavesAereasNiv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilderPortaNavesAereasNiv1::ConstruirHangar()
{
	FVector Location = FVector(0, 0, 300);
	FRotator Rotation = FRotator(0.0f, 180.0f, 0.0f);
	FVector Escala = FVector(3.0f, 3.0f, 3.0f);
	Hangar = GetWorld()->SpawnActor<AHangar>(AHangar::StaticClass(), Location, Rotation);
	Hangar->SetActorScale3D(Escala);
	PortaNaveAerea->SetHangar(Hangar, " Hangar ");
}

void ABuilderPortaNavesAereasNiv1::ConstruirCentrodeMuniciones()
{
	FVector Location = FVector(0, 200, 300);
	FRotator Rotation = FRotator(0.0f, 180.0f, 0.0f);
	FVector Location2 = FVector(0, -200, 300);
	CentroMuniciones = GetWorld()->SpawnActor<ACentroMuniciones>(ACentroMuniciones::StaticClass(), Location, Rotation);
	CentroMuniciones = GetWorld()->SpawnActor<ACentroMuniciones>(ACentroMuniciones::StaticClass(), Location2, Rotation);
	PortaNaveAerea->SetCentrodeMuniciones(CentroMuniciones, " Centro de Municiones ");
}

void ABuilderPortaNavesAereasNiv1::ConstruirEscudos()
{
	FVector Location = FVector(-100, -200, 90);
	FRotator Rotation = FRotator(0.0f, 90.0f, 0.0f);
	Escudo = GetWorld()->SpawnActor<AEscudo>(AEscudo::StaticClass(), Location, Rotation);
	PortaNaveAerea->SetEscudos(Escudo, " Escudo ");
}

void ABuilderPortaNavesAereasNiv1::ConstruirMotor()
{
	FVector Location = FVector(200, 0, 300);
	FRotator Rotation = FRotator(-90.0f, 0.0f, 0.0f);
	Motor = GetWorld()->SpawnActor<AMotor>(AMotor::StaticClass(), Location, Rotation);
	PortaNaveAerea->SetMotor(Motor, " Motor ");
}

APortaNavesAereas* ABuilderPortaNavesAereasNiv1::GetPortaNaveAerea()
{
	return PortaNaveAerea;

}



