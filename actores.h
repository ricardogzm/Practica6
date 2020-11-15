#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>


void barbero(int semaforos, int cortes, int **clEsperando);
void cliente(int semaforos, int **clEsperando);