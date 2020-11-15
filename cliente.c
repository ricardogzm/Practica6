#include "actores.h"
#include "semaforos.h"
#include <time.h>

void cliente(int semaforos, int **clEsperando) {
    srandom(time(NULL));
    FILE *fd;
    while (1) {
        for(int i=0; i<random()%15; i++){
            if (fork() == 0) {
                manejarSemaforo(semaforos, mutex, down); //region critica
                if ((**clEsperando) < sillas) { //comprobar que haya sillas desocupadas
                    fd= fopen("cliente.txt", "a");
                    fprintf(fd,"\n Ha entrado un cliente, numero: %d \n", getpid());
                    fclose(fd);
                    (**clEsperando)++; //Aumenta el numero de clientees en espéra
                    manejarSemaforo(semaforos, clientes, up); //Si esta dormido, se despierta al barbero
                    manejarSemaforo(semaforos, mutex, up); //abre la memoria compartida
                    manejarSemaforo(semaforos, barberoDisponible, down); //comienza una ves que el barbero esta desocupado
                    fd= fopen("cliente.txt", "a");
                    fprintf(fd,"Se le ha cortado el cabello al cliente: %d\n", getpid());
                    fclose(fd);
                } else {
                    fprintf(fd,"Ya no hay espacio en la peluqueria \n");
                    fclose(fd);
                    manejarSemaforo(semaforos, mutex, up); //la peluqueria esta llena. no esperar
                }
                exit(0);
            }
            sleep(2);
        }
    }
}