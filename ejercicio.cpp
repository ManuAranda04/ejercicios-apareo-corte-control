#include <iostream>
#include <string>
//Una empresa de transporte cuenta con camiones de diferente tamaño.
//Al finalizar el día se cuenta con los datos de cada viaje ordenados por patente en forma ascendente:
//- Patente
//- Hora de inicio
//- Hora de fin
//- Kilómetros recorridos
//- Importe
//Y en forma separada, los datos de cada vehículo:
//- Patente
//- Modelo
//- Consumo por kilómetro
//Para escribir el código, se asume que los datos ya están cargados en vectores estáticos y que cada vector tiene una variable asociada que indica la cantidad de elementos cargados.
//Se asume que cada vehículo realiza al menos un viaje en el día.
//1) Escribir una función que ordene el vector de vehículos por modelo (ordenamiento burbuja).
//2) Escribir una función que busque en el vector de vehículos por patente y devuelva la posición en el vector (búsqueda binaria).
//3) Escribir una función que calcule el costo total del combustible utilizado por todos los camiones en el día.
//4) Escribir una función que indique la patente del vehículo con mejor y peor rendimiento, de acuerdo al consumo total de combustible en relación con el total de los importes cobrados por los viajes.

struct VIAJES
{
    std::string patente;
    int horaInicio;
    int horaFin;
    float kmRecorridos;
    float importe;
};


struct VEHICULOS
{
    std::string patente;
    std::string modelo;
    float consumoPorKM;
};

void ordenamientoModelo(VEHICULOS vehiculos[], int nTotal){
    int i = 0;
    bool ordenado = false;

    while(i < nTotal && !ordenado){
        ordenado = true;
        for(int j = 0; j < nTotal-i-1; j++){
            if(vehiculos[j].modelo > vehiculos[j+1].modelo){
                VEHICULOS aux = vehiculos[j];
                vehiculos[j] = vehiculos[j+1];
                vehiculos[j+1] = aux;
                ordenado = false;
            }
        }
        i++;
    }
}

void ordenamientoPatente(VEHICULOS vehiculos[], int nTotal){
    int i = 0;
    bool ordenado = false;

    while(i < nTotal && !ordenado){
        ordenado = true;
        for(int j = 0; j < nTotal-i-1; j++){
            if(vehiculos[j].patente > vehiculos[j+1].patente){
                VEHICULOS aux = vehiculos[j];
                vehiculos[j] = vehiculos[j+1];
                vehiculos[j+1] = aux;
                ordenado = false;
            }
        }
        i++;
    }
}

int busquedaPatente(VEHICULOS vehiculos[], int nTotal, std::string patenteBuscada){
    int inicio = 0, fin = nTotal - 1;

    while (fin >= inicio)
    {
        int mitad = inicio + (fin - inicio) / 2;

        if(vehiculos[mitad].patente == patenteBuscada)
            return mitad;
        if (vehiculos[mitad].patente > patenteBuscada)
        {
            fin = mitad - 1;
        } else {
            inicio = mitad + 1;
        }
    }

    return -1;
}

float costoTotalCombustible(VIAJES viajes[], int nViajes, VEHICULOS vehiculos[], int nVehiculos, float precio){
    float costoTotal = 0;

    for(int i = 0; i < nViajes; i++){
        std::string patente = viajes[i].patente;

        int pos = busquedaPatente(vehiculos, nVehiculos, patente);
        if (pos != -1) {
            float costo = (viajes[i].kmRecorridos * vehiculos[pos].consumoPorKM) * precio;
            costoTotal += costo;
        }
    }

    return costoTotal;
}

void mejorPeorRendimiento(VIAJES viajes[], int nViajes, VEHICULOS vehiculos[], int nVehiculos, float precioLitro){
    float mejorRendimiento = -1.0;
    std::string patenteMejor;

    float peorRendimiento = 150000000.0;
    std::string patentePeor;

    int i = 0;
    while (i < nViajes) {
        std::string patenteActual = viajes[i].patente;

        float totalKmGrupo = 0;
        float totalImporteGrupo = 0;

        while (i < nViajes && viajes[i].patente == patenteActual) {
            totalKmGrupo += viajes[i].kmRecorridos;
            totalImporteGrupo += viajes[i].importe;
            i++;
        }

        int posVehiculo = busquedaPatente(vehiculos, nVehiculos, patenteActual);

        if (posVehiculo != -1) {
            float consumo = vehiculos[posVehiculo].consumoPorKM;
            float costoCombustibleGrupo = (totalKmGrupo * consumo) * precioLitro;
            
            if (costoCombustibleGrupo > 0) {
                float rendimientoActual = totalImporteGrupo / costoCombustibleGrupo;

                if (mejorRendimiento == -1.0) {
                    mejorRendimiento = rendimientoActual;
                    patenteMejor = patenteActual;
                    peorRendimiento = rendimientoActual;
                    patentePeor = patenteActual;
                }else{
                    if (rendimientoActual > mejorRendimiento) {
                        mejorRendimiento = rendimientoActual;
                        patenteMejor = patenteActual;
                    }
                    if (rendimientoActual < peorRendimiento) {
                        peorRendimiento = rendimientoActual;
                        patentePeor = patenteActual;
                    }
                }
            }
        }
    }

    std::cout << "Mejor rendimiento: "<<patenteMejor<<" ("<<mejorRendimiento<<")" << std::endl;
    std::cout << "Peor rendimiento: "<<patentePeor<< " ("<<peorRendimiento<<")" << std::endl;
}

int main(){
    const int TAMANIO_MAXIMO = 4;
    VEHICULOS vehiculos[TAMANIO_MAXIMO] = {
        {"5ASD4 A34", "Toyota", 12.5},
        {"1U5DA B4J", "Chevrolet", 18.5},
        {"ADO31 65N", "Toyota", 14.5},
        {"A5O31 63N", "Ford", 16.5}
    };
    VIAJES viajes[TAMANIO_MAXIMO] = {
        {"5ASD4 A34", 1600, 1800, 20, 1000},
        {"1U5DA B4J", 1200, 2000, 40, 1800},
        {"ADO31 65N", 1100, 1500, 25, 1200},
        {"A5O31 63N", 1100, 1600, 30, 1400}
    };
    
    int nTotal = 4;
    
    ordenamientoModelo(vehiculos, nTotal);

    std::cout << "Vehiculos ordenados por modelo: " << std::endl;
    for(int i = 0; i < nTotal; i++){
        std::cout << "\t-"<<vehiculos[i].modelo << std::endl;
    }

    ordenamientoPatente(vehiculos, nTotal);

    std::string patenteBuscada;
    std::cout << "Ingrese la patente a buscar" << std::endl;
    std::getline(std::cin, patenteBuscada);
    int posicion = busquedaPatente(vehiculos, nTotal, patenteBuscada);
    std::cout << "La patente buscada se encuentra en la posicion "<<posicion+1<< std::endl;

    float precioLitro = 400.0;
    float total = costoTotalCombustible(viajes, nTotal, vehiculos, nTotal, precioLitro);
    std::cout << "El costo total del combustible es: $" << total << std::endl;

    mejorPeorRendimiento(viajes, nTotal, vehiculos, nTotal, precioLitro);

    return 0;
}