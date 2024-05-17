// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderPortaNavesAereasNiv1.h"
#include "PortaNavesAereas.h"

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

	//Spawn the PNA Actors
	PortaNaveAerea = GetWorld()->SpawnActor<APortaNavesAereas>(APortaNavesAereas::StaticClass());
	//Attach it to the Builder (this)
	PortaNaveAerea->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called every frame
void ABuilderPortaNavesAereasNiv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilderPortaNavesAereasNiv1::ConstruirHangar()
{
	if (!PortaNaveAerea) {
		UE_LOG(LogTemp, Error, TEXT("BuildSwimmingPool():Lodging is NULL, make sure it's initialized.")); return; 
		PortaNaveAerea->SetHangar("Hangar");
	}
}

void ABuilderPortaNavesAereasNiv1::ConstruirCentrodeMuniciones()
{
	if (!PortaNaveAerea) {
		UE_LOG(LogTemp, Error, TEXT("BuildSwimmingPool():Lodging is NULL, make sure it's initialized.")); return;
		PortaNaveAerea->SetCentrodeMuniciones("Centro de Municiones");
	}
}

//void ABuilderPortaNavesAereasNiv1::ConstruirCentrodeMuniciones()
//{
//	if (PortaNaveAerea)
//	{
//		// Llama al método en PortaNavesAereas para recargar las municiones
//		PortaNaveAerea->RecargarBalas(PortaNaveAerea->GetMaxBalas() - PortaNaveAerea->GetNumBalas()); // Asegúrate de no exceder el máximo
//		UE_LOG(LogTemp, Warning, TEXT("Municiones recargadas en el hangar."));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("PortaNaveAerea is NULL, make sure it's initialized."));
//	}
//}

void ABuilderPortaNavesAereasNiv1::ConstruirEscudos()
{
	if (!PortaNaveAerea) {
		UE_LOG(LogTemp, Error, TEXT("BuildSwimmingPool():Lodging is NULL, make sure it's initialized.")); return; 
		PortaNaveAerea->SetCentrodeEscudos("Centro de Escudos");
	}
}

APortaNavesAereas* ABuilderPortaNavesAereasNiv1::GetPortaNaveAerea()
{
	return PortaNaveAerea;
	
}

