#include "semaforos.h"
#include "actores.h"

int main(){

    int memoria, *clEsperando; //Recurso compartido entre los procesos
    int semaforos; //semaforos
    int cortes=0;
    key_t semkey = 0x100;
    key_t shmkey = 0x200;

    if((semaforos = iniciarSemaforo(semkey)) < 0){ //inicializacion de semaforos
        exit(1); //si fallo al iniciar termina el proceso
    }

    if((memoria = shmget(shmkey ,sizeof(int), 0600 |IPC_CREAT)) == -1){ //creacion de memoria comparitda
        perror("Error");
        exit(1);
    }

    if((clEsperando = (int*)shmat(memoria, 0, 0))== (int *)-1){ //ligado de memoria
        perror("Error");
        exit(1);
    }

    (*clEsperando) = 0;
    manejarSemaforo(semaforos, mutex, up);


    if(fork()==0) {
        barbero(semaforos, cortes, &clEsperando);
    }
    if(fork()==0) {
        cliente(semaforos, &clEsperando);//Cliente
    }

}
