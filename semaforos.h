#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>


#define up 1
#define down -1

#define barberoDisponible 0 //mutex para disponibilidad de barbero
#define clientes 1 //semaforo de clientes en la sala de espera
#define mutex 2 //mutex para disponibilidad de sillas

#define sillas 10 //Total de sillas
#define SEMPERM 0600

int iniciarSemaforo(key_t semkey);
int manejarSemaforo(int semid, int numsem, int op);

