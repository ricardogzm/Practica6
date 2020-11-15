#include "actores.h"
#include "semaforos.h"
#include <time.h>

void cliente(int semaforos, int **clEsperando) {
    srandom(time(NULL));
    FILE *fd;
    fd= fopen("cliente.txt", "w");
    while (1) {
        for(int i=0; i<random()%15; i++;){
            if (fork() == 0) {
                manejarSemaforos(semaforos, mutex, down); //entrar en region critica
                if ((*clientesEsperando) < sillas) { //comprobar que haya sillas desocupadas
                    fprintf("\n Se agrego el cliente: %d \n", getpid());
                    (*clientesEsperando) = (*clientesEsperando) + 1; //incrementar cuenta de clientees en espéra
                    manejarSemaforos(semaforos, clientes, up); //despertar al peluquero si es necesario
                    manejarSemaforos(semaforos, mutex, up); //liberar acceso a recurso compartido
                    manejarSemaforos(semaforos, barberoListo, down); //esperar a que el barbero este libre
                    fprintf("el cliente %d fue atendido \n", getpid());  //sentarse en la silla del barbero y ser atendido
                } else {
                    fprintf("la peluqueria esta llena \n");
                    manejarSemaforos(semaforos, mutex, up); //la peluqueria esta llena. no esperar
                }
            }
        }
    }
    fclose(fd);
}