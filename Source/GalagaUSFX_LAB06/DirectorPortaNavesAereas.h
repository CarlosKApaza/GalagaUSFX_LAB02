// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderPortaNavesAereas.h"

#include "DirectorPortaNavesAereas.generated.h"

UCLASS()
class GALAGAUSFX_LAB06_API ADirectorPortaNavesAereas : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectorPortaNavesAereas();
private:
	IBuilderPortaNavesAereas* BuilderPortaNavesAereas; // Instanciamos una direccion de la interfaz BuilderPortaNavesAereas
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Creates the buildings
	void ConstruirPortaNaveAerea(); // Funcion que construye la PortaNaveAerea
	void SetBuilderPortaNavesAereas(AActor* Builder); // Funcion que asigna el BuilderPortaNavesAereas 

	class APortaNavesAereas* GetPortaNaveAerea();


};
