#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "mem_comp.h"

key_t shmkey = 0x200;

int * attachMemoryBlock(int size) {
    int *resultado;
    int id_bloque;
    //creacion de bloque
    if((id_bloque = shmget(shmkey, size, 0644 |IPC_CREAT)) == -1){ 
        perror("Error al crear bloque.");
        exit(1);
    }

    //mapear el bloque compartido en la memoria del proceso y devolver un apuntador

    resultado = shmat(id_bloque, NULL, 0);
    if (resultado == (int *)-1) {
        perror("Error al mapear bloque.");
        exit(1);
    }

    return resultado;
}

void detachMemoryBlock(int *block) {
    shmdt(block);
    printf("Block detached.\n");
}

void destroyMemoryBlock() {
    int id_bloque = shmget(shmkey, sizeof(int), 0);

    if (id_bloque == -1) {
        perror("Error al obtener bloque.");
        exit(1);
    }

    if (shmctl(id_bloque, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar bloque.");
        exit(1);
    }
}
