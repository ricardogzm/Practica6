#include "actores.h"
#include "semaforos.h"
#include "mem_comp.h"
#include <stdio.h>
#include <time.h>

void cliente(int semaforos) {
    srandom(time(NULL));
    FILE *fd;

    int *clEsperando = attachMemoryBlock(sizeof(int));
    if (clEsperando == NULL) {
        printf("Error: no se pudo obtener el bloque.");
        exit(1); 
    }
    while (1) {
        for(int i=0; i<random()%15; i++){
            if (fork() == 0) {
                manejarSemaforo(semaforos, mutex, down); //entrar en region critica
                if ((*clEsperando) < sillas) { //comprobar que haya sillas desocupadas
                    fd= fopen("cliente.txt", "a");
                    fprintf(fd,"\n Se agrego el cliente: %d \n", getpid());
                    fclose(fd);
                    (*clEsperando)++; //incrementar cuenta de clientees en espéra
                    manejarSemaforo(semaforos, clientes, up); //despertar al peluquero si es necesario
                    manejarSemaforo(semaforos, mutex, up); //liberar acceso a recurso compartido
                    manejarSemaforo(semaforos, barberoDisponible, down); //esperar a que el barbero este libre
                    fd= fopen("cliente.txt", "a");
                    fprintf(fd,"el cliente %d fue atendido \n", getpid());  //sentarse en la silla del barbero y ser atendido
                    fclose(fd);
                } else {
                    fd= fopen("cliente.txt", "a");
                    fprintf(fd,"la peluqueria esta llena \n");
                    fclose(fd);
                    manejarSemaforo(semaforos, mutex, up); //la peluqueria esta llena. no esperar
                }
                
                exit(0);
            }
        }
        sleep(3);
    }
}
