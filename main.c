#include "semaforos.h"
#include "actores.h"
#include "mem_comp.h"

//#define BLOCK_SIZE sizeof(int)

int main(){

    int memoria; //Recurso compartido entre los procesos
    int semaforos; //semaforos
    int cortes=0;
    FILE *fd;
    key_t semkey = 0x100;
    key_t shmkey = 0x200;

    int *clEsperando = attachMemoryBlock(sizeof(int));

    if (clEsperando == NULL) {
        printf("Error: no se pudo obtener el bloque.");
        exit(1); 
    }
    *clEsperando = 0;
    detachMemoryBlock(clEsperando);

    //Crear archivos nuevos
    fd= fopen("cliente.txt", "w");
    fclose(fd);
    fd= fopen("barbero.txt", "w");
    fclose(fd);

    if((semaforos = iniciarSemaforo(semkey)) < 0){ //inicializacion de semaforos
        exit(1); //si fallo al iniciar termina el proceso
    }

/*     if((memoria = shmget(shmkey ,sizeof(int), 0600 |IPC_CREAT)) == -1){ //creacion de memoria comparitda */
/*         perror("Error"); */
/*         exit(1); */
/*     } */

/*     if((clEsperando = (int*)shmat(memoria, 0, 0))== (int *)-1){ //ligado de memoria */
/*         perror("Error"); */
/*         exit(1); */
/*     } */

/*     (*clEsperando) = 0; */
    /* manejarSemaforo(semaforos, mutex, up); */


    if(fork()==0) {
        barbero(semaforos, cortes);
    }
    if(fork()==0) {
        cliente(semaforos);//Cliente
    }

    while (1){

    }
}
