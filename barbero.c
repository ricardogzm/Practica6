#include "actores.h"
#include "semaforos.h"


void barbero(int semaforos, int cortes, int **clEsperando) {
    FILE *fd;
    fd= fopen("barbero.txt", "w");
    while (1){
        fprintf(fd,"El barbero esta: Dormido\n Cortes hechos: %d \n", cortes);

        manejarSemaforo(semaforos, clientes, down); //barbero durmiendo si hay 0 clientes
        manejarSemaforo(semaforos, mutex, down); //espera para adquirir acceso a sillas disponibles

        (*clEsperando) = (*clEsperando) - 1; //decrementar un cliente en la lista de espera
        cortes++; //aumenta el numero de cortes
        fprintf(fd,"El barbero esta: ocupado \n Cortes hechos: %d \n", cortes);
        sleep(5);

        manejarSemaforo(semaforos, barberoDisponible, up); //el barbero esta listo para cortar el pelo
        manejarSemaforo(semaforos, mutex, up);  //libera acceso a sillas disponibles
    }
    fclose(fd);
}