// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanoPortaNavesAereas.h"

#include "PortaNavesAereas.generated.h"

class UStaticMeshComponent;

UCLASS()
class GALAGAUSFX_LAB06_API APortaNavesAereas : public AActor, public IPlanoPortaNavesAereas
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortaNavesAereas();
private:
	FString Hangar;
	FString CentroMuniciones;
	FString Escudos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Metodos 
	void SetHangar(FString _hangar) override;
	void SetCentrodeMuniciones(FString _Municiones) override; // 
	void SetCentrodeEscudos(FString _escudos) override;

	void CaracteristicasPortaNaveAerea();


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MallaPortaNave;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PortaNavesAereas")
    TArray<APortaNavesAereas*> Almacenamiento;*/

	// FUNCIONES AGREGADAS PARA RECARGAR BALAS
public:
	// Aumenta el número de balas disponibles
	void RecargarBalas(int32 NumBalasRecargar);

private:
	int32 NumBalas; // Número actual de balas
	int32 MaxBalas; // Número máximo de balas permitidas

public: 
	int32 GetNumBalas() const { return NumBalas; }
	int32 GetMaxBalas() const { return MaxBalas; }
};
