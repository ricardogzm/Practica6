#include "actores.h"
#include "semaforos.h"
#include "mem_comp.h"
#include <stdio.h>


void barbero(int semaforos, int cortes) {
    FILE *fd;
    int *clEsperando = attachMemoryBlock(sizeof(int));

    if (clEsperando == NULL) {
        printf("Error: no se pudo obtener el bloque.");
        exit(1); 
    }

    while (1){
        fd= fopen("barbero.txt", "a");
        fprintf(fd,"El barbero esta: Dormido\n Cortes hechos: %d \n", cortes);
        fclose(fd);
        manejarSemaforo(semaforos, clientes, down); //barbero durmiendo si hay 0 clientes
        manejarSemaforo(semaforos, mutex, down); //espera para adquirir acceso a sillas disponibles

        (*clEsperando)--; //decrementar un cliente en la lista de espera
        cortes++; //aumenta el numero de cortes
        fd= fopen("barbero.txt", "a");
        fprintf(fd,"El barbero esta: ocupado \n Cortes hechos: %d \n", cortes);
        fclose(fd);

        manejarSemaforo(semaforos, barberoDisponible, up); //el barbero esta listo para cortar el pelo
        manejarSemaforo(semaforos, mutex, up);  //libera acceso a sillas disponibles

    }

}
